# CAD_Exchanger_Test

This C++ project implements support for a hierarchy of 3D curves, including circles, ellipses, and 3D helixes. The program performs the following tasks:

1. **Support for Multiple 3D Geometric Curves:**
   - Circles
   - Ellipses
   - 3D Helixes

2. **Random Generation of Curves:**
   - A container (e.g., vector or list) is populated with randomly generated objects of different curve types. The curves are created with random parameters.

3. **Printing Coordinates and Derivatives:**
   - Coordinates of points and derivatives of all curves in the container are printed at t=PI/4.

4. **Creating a Container of Circles:**
   - A second container is populated with circles from the first container. The second container shares circles from the first one through pointers.

5. **Sorting Circles by Radius:**
   - The second container, containing circles, is sorted in ascending order based on the circles' radii.

6. **Computing Total Sum of Radii:**
   - The program computes the total sum of radii of all curves in the second container.

## Usage

To use this project, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/MrSteelRat/CAD_Exchanger_Test.git
    ```

2. Build the project:

    ```bash
    cd CAD_Exchanger_Test
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the executable:

    ```bash
    ./CAD_Exchanger_Test
    ```

### Windows

1. Clone the repository:

    ```cmd
    git clone https://github.com/MrSteelRat/CAD_Exchanger_Test.git
    ```

2. Open the project in Visual Studio:

   - Launch Visual Studio.
   - Open the project located in the `CAD_Exchanger_Test` directory.

3. Build the project:

   - Build the project using the Visual Studio IDE.

4. Run the executable:

   - Run the generated executable from the Visual Studio output directory.

Feel free to explore the code for more details on the implementation.

