#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <optional>
#include <unordered_set>
#include <utility>
#include <vector>

using seq = std::list<std::list<std::pair<int, int>>>;

void ThinOut(seq& v, const seq::size_type n)
{
  assert(n > 2);

  seq::size_type i = 0;
  std::optional<std::reference_wrapper<std::pair<int, int>>> prev;
  std::vector<std::reference_wrapper<std::pair<int, int>>> dubs;

  std::ranges::for_each(
      v,
      [&](auto& w)
      {
        std::ranges::for_each(
            w,
            [&](auto& p)
            {
              if (prev.has_value() && prev->get().second == p.second)
              {
                ++i;
              }
              else
              {
                if (!dubs.empty() && prev.has_value() &&
                    std::addressof(dubs.at(dubs.size() - 1).get()) ==
                        std::addressof(prev->get()))
                {
                  dubs.pop_back();
                }

                i = 0;
              }

              if (i > 0 && !!((i + 1) % n))
              {
                dubs.push_back(p);
              }

              prev = p;
            });
      });

  std::ranges::for_each(
      v,
      [&](auto& w)
      {
        w.erase(
            std::ranges::remove_if(w,
                                   [&](auto& p)
                                   {
                                     if (auto it = std::ranges::find_if(
                                             dubs,
                                             [&](auto& d) {
                                               return std::addressof(p) ==
                                                      std::addressof(d.get());
                                             });
                                         it != dubs.end())
                                     {
                                       dubs.erase(it);
                                       return true;
                                     }
                                     return false;
                                   })
                .begin(),
            w.end());
      });

  v.erase(std::ranges::remove_if(v, [](auto& w) { return w.empty(); }).begin(),
          v.end());
}

void Print(const seq& v)
{
  seq::size_type i = 0;
  std::ranges::for_each(v,
                        [&](const auto& w)
                        {
                          decltype(w.size()) j = 0;
                          std::ranges::for_each(w,
                                                [&](const auto& p)
                                                {
                                                  std::cout << "(" << p.first
                                                            << ", " << p.second
                                                            << ")";
                                                  if (j++ < w.size() - 1)
                                                    std::cout << " ";
                                                });
                          if (i++ < v.size() - 1) std::cout << ", ";
                        });
  std::cout << std::endl;
}

int main()
{
  {
    seq sequence{
        {{1, 10}, {2, 11}},
        {{3, 11}},
        {{4, 11}},
        {{5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}},
    };
    Print(sequence);
    ThinOut(sequence, 3);
    Print(sequence);
  }
  {
    seq sequence{
        {{1, 10}, {2, 11}},
        {{3, 11}},
        {{4, 11}},
        {{5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}},
    };
    Print(sequence);
    ThinOut(sequence, 4);
    Print(sequence);
  }
}
