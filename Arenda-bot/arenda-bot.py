package main

import (
	"context"
	"fmt"
	"strings"
	"time"

	"github.com/go-telegram/bot"
	"github.com/go-telegram/bot/models"
)

// Структуры данных
type Booking struct {
	ID           int
	UserID       int64
	Room         string
	Date         string
	Start        string
	End          string
	Status       string
	PaymentProof string
}

type UserState struct {
	Current      string
	SelectedRoom string
	SelectedDate string
	SelectedTime string
}

var (
	bookings    []Booking
	userStates        = make(map[int64]*UserState)
	adminChatID int64 = 445537275 // Замените на реальный ID администратора
	timeSlots         = []string{"10:00", "12:00", "14:00", "16:00", "18:00", "20:00"}
	prices            = map[string]int{"Зал 1": 1500, "Зал 2": 2000, "Зал 3": 2500}
)

func main() {
	ctx := context.Background()
	token := "ч" // Замените на реальный токен бота

	opts := []bot.Option{
		bot.WithDefaultHandler(handler),
	}

	b, err := bot.New(token, opts...)
	if err != nil {
		panic(err)
	}

	b.Start(ctx)
}

func handler(ctx context.Context, b *bot.Bot, update *models.Update) {
	if update.Message != nil {
		handleMessage(ctx, b, update.Message)
	} else if update.CallbackQuery != nil {
		handleCallback(ctx, b, update.CallbackQuery)
	}
}

func handleMessage(ctx context.Context, b *bot.Bot, msg *models.Message) {
	chatID := msg.Chat.ID

	// Обработка документов (подтверждение оплаты)
	if msg.Document != nil || msg.Photo != nil {
		userID := msg.From.ID
		processPaymentProof(ctx, b, msg, userID)
		return
	}

	// Главное меню
	sendMainMenu(ctx, b, chatID)
}

func handleCallback(ctx context.Context, b *bot.Bot, callback *models.CallbackQuery) {
	userID := callback.From.ID
	chatID := callback.Message.Chat.ID // Исправлено получение chatID
	data := callback.Data

	switch {
	case data == "rent":
		showRoomSelection(ctx, b, chatID)
	case strings.HasPrefix(data, "room_"):
		room := strings.Split(data, "_")[1]
		selectRoom(ctx, b, chatID, userID, room)
	case strings.HasPrefix(data, "date_"):
		date := strings.Split(data, "_")[1]
		selectDate(ctx, b, chatID, userID, date)
	case strings.HasPrefix(data, "time_"):
		timeSlot := strings.Split(data, "_")[1]
		selectTime(ctx, b, chatID, userID, timeSlot)
	case data == "confirm_booking":
		confirmBooking(ctx, b, chatID, userID)
	case data == "my_bookings":
		showUserBookings(ctx, b, chatID, userID)
	}

	b.AnswerCallbackQuery(ctx, &bot.AnswerCallbackQueryParams{
		CallbackQueryID: callback.ID,
	})
}

func sendMainMenu(ctx context.Context, b *bot.Bot, chatID int64) {
	kb := [][]models.InlineKeyboardButton{
		{{Text: "Аренда студий", CallbackData: "rent"}},
		{{Text: "Мои бронирования", CallbackData: "my_bookings"}},
	}

	params := &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        "Главное меню:",
		ReplyMarkup: models.InlineKeyboardMarkup{InlineKeyboard: kb},
	}

	b.SendMessage(ctx, params)
}

func showRoomSelection(ctx context.Context, b *bot.Bot, chatID int64) {
	kb := [][]models.InlineKeyboardButton{
		{{Text: "Зал 1", CallbackData: "room_Зал 1"}},
		{{Text: "Зал 2", CallbackData: "room_Зал 2"}},
		{{Text: "Зал 3", CallbackData: "room_Зал 3"}},
	}

	params := &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        "Выберите зал для аренды:",
		ReplyMarkup: models.InlineKeyboardMarkup{InlineKeyboard: kb},
	}

	b.SendMessage(ctx, params)
}

func selectRoom(ctx context.Context, b *bot.Bot, chatID int64, userID int64, room string) {
	// Инициализация состояния пользователя
	if _, ok := userStates[userID]; !ok {
		userStates[userID] = &UserState{}
	}
	userStates[userID].SelectedRoom = room
	userStates[userID].Current = "date_selection"

	// Показать календарь (7 ближайших дней)
	kb := [][]models.InlineKeyboardButton{}
	today := time.Now()
	for i := 1; i <= 7; i++ {
		date := today.AddDate(0, 0, i).Format("02.01.2006")
		kb = append(kb, []models.InlineKeyboardButton{
			{Text: date, CallbackData: "date_" + date},
		})
	}

	params := &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        "Выберите дату:",
		ReplyMarkup: models.InlineKeyboardMarkup{InlineKeyboard: kb},
	}

	b.SendMessage(ctx, params)
}

func selectDate(ctx context.Context, b *bot.Bot, chatID int64, userID int64, date string) {
	state := userStates[userID]
	state.SelectedDate = date
	state.Current = "time_selection"

	// Показать доступное время
	kb := [][]models.InlineKeyboardButton{}
	for _, slot := range timeSlots {
		if isTimeSlotAvailable(state.SelectedRoom, date, slot) {
			kb = append(kb, []models.InlineKeyboardButton{
				{Text: slot, CallbackData: "time_" + slot},
			})
		}
	}

	params := &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        "Выберите время начала:",
		ReplyMarkup: models.InlineKeyboardMarkup{InlineKeyboard: kb},
	}

	b.SendMessage(ctx, params)
}

func selectTime(ctx context.Context, b *bot.Bot, chatID int64, userID int64, timeSlot string) {
	state := userStates[userID]
	state.SelectedTime = timeSlot
	state.Current = "confirmation"

	price := prices[state.SelectedRoom]

	// Кнопки подтверждения
	kb := [][]models.InlineKeyboardButton{
		{{Text: "Подтвердить бронь", CallbackData: "confirm_booking"}},
	}

	text := fmt.Sprintf(
		"Детали бронирования:\nЗал: %s\nДата: %s\nВремя: %s\nСтоимость: %d руб.\n\nПосле оплаты отправьте скриншот чека.",
		state.SelectedRoom, state.SelectedDate, timeSlot, price,
	)

	params := &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        text,
		ReplyMarkup: models.InlineKeyboardMarkup{InlineKeyboard: kb},
	}

	b.SendMessage(ctx, params)
}

func confirmBooking(ctx context.Context, b *bot.Bot, chatID int64, userID int64) {
	state := userStates[userID]

	// Создание бронирования
	newBooking := Booking{
		UserID:       userID,
		Room:         state.SelectedRoom,
		Date:         state.SelectedDate,
		Start:        state.SelectedTime,
		Status:       "Ожидает оплаты",
		PaymentProof: "",
	}
	bookings = append(bookings, newBooking)

	// Отправить инструкцию по оплате
	price := prices[state.SelectedRoom]
	text := fmt.Sprintf(
		"Бронь создана! Пожалуйста, оплатите %d руб. по реквизитам:\n\nБанк: ...\nСчет: ...\n\nОтправьте скриншот чека для подтверждения.",
		price,
	)

	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: chatID,
		Text:   text,
	})

	// Сброс состояния
	delete(userStates, userID)
}

func processPaymentProof(ctx context.Context, b *bot.Bot, msg *models.Message, userID int64) {
	chatID := msg.Chat.ID

	// Поиск последней брони пользователя
	var lastBooking *Booking
	for i := len(bookings) - 1; i >= 0; i-- {
		if bookings[i].UserID == userID {
			lastBooking = &bookings[i]
			break
		}
	}

	if lastBooking == nil {
		b.SendMessage(ctx, &bot.SendMessageParams{
			ChatID: chatID,
			Text:   "У вас нет активных бронирований",
		})
		return
	}

	// Обновление статуса
	lastBooking.Status = "Подтверждается"
	lastBooking.PaymentProof = "file_id_here" // В реальности сохранить file_id

	// Уведомление администратора
	adminText := fmt.Sprintf(
		"Новая оплата!\nПользователь: %s %s\nЗал: %s\nДата: %s\nВремя: %s",
		msg.From.FirstName, msg.From.LastName,
		lastBooking.Room, lastBooking.Date, lastBooking.Start,
	)

	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: adminChatID,
		Text:   adminText,
	})

	// Подтверждение пользователю
	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: chatID,
		Text:   "Оплата получена! Администратор проверит документ и подтвердит бронь.",
	})
}

func showUserBookings(ctx context.Context, b *bot.Bot, chatID int64, userID int64) {
	var userBookings []Booking
	for _, booking := range bookings {
		if booking.UserID == userID {
			userBookings = append(userBookings, booking)
		}
	}

	if len(userBookings) == 0 {
		b.SendMessage(ctx, &bot.SendMessageParams{
			ChatID: chatID,
			Text:   "У вас нет активных бронирований",
		})
		return
	}

	text := "Ваши бронирования:\n\n"
	for i, booking := range userBookings {
		text += fmt.Sprintf(
			"%d. %s - %s\nЗал: %s\nВремя: %s\nСтатус: %s\n\n",
			i+1, booking.Date, booking.Start, booking.Room, booking.Status,
		)
	}

	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: chatID,
		Text:   text,
	})
}

func isTimeSlotAvailable(room, date, timeSlot string) bool {
	for _, booking := range bookings {
		if booking.Room == room &&
			booking.Date == date &&
			booking.Start == timeSlot &&
			(booking.Status == "Подтверждено" || booking.Status == "Подтверждается") {
			return false
		}
	}
	return true
}
