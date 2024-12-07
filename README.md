# Open CASCADE Installation on Raspberry Pi

This guide provides step-by-step instructions to clone, build, and install the Open CASCADE Technology (OCCT) repository on a Raspberry Pi running Raspbian OS.


## Prerequisites

Before starting the installation, ensure your Raspberry Pi is updated and ready for installation.

### Update the System
Run the following commands to update your system:
```bash
sudo apt update
sudo apt upgrade -y
```

### Install Required Dependencies
Install the essential build tools and libraries required by Open CASCADE:
```bash
sudo apt install build-essential cmake git libx11-dev libfreetype6-dev libgl1-mesa-dev libxext-dev libxrender-dev libtbb-dev tcl-dev tk-dev doxygen -y
```



## Cloning the Repository

Clone the Open CASCADE source code from its official GitHub repository.

To avoid network-related issues or large history downloads, follow these steps:

1. Increase Git buffer size to prevent fetch issues:
   ```bash
   git config --global http.postBuffer 524288000
   ```

2. Clone the repository with minimal history (shallow clone):
   ```bash
   git clone --depth 1 https://github.com/Open-Cascade-SAS/OCCT.git
   cd OCCT
   ```


## Building Open CASCADE

Follow these steps to build Open CASCADE:

### Step 1: Create a Build Directory
Create a separate directory for building the source code:
```bash
mkdir build
cd build
```

### Step 2: Configure the Build
Run the `cmake` command to configure the build environment:
```bash
cmake .. -DUSE_FREEIMAGE=OFF -DUSE_GL2PS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
```

#### Flags Explanation
- `-DUSE_FREEIMAGE=OFF`: Disables FreeImage support (optional dependency).
- `-DUSE_GL2PS=OFF`: Disables GL2PS support (optional dependency).
- `-DCMAKE_BUILD_TYPE=Release`: Optimized build for better performance.
- `-DCMAKE_INSTALL_PREFIX=/usr/local`: Specifies the installation directory.

### Step 3: Build the Source Code
Compile the source code using `make`:
```bash
make -j$(nproc)
```
- The `-j$(nproc)` flag uses all available CPU cores to speed up the build process.



## Installing Open CASCADE

After the build completes successfully, install Open CASCADE:

```bash
sudo make install
```


## Verifying the Installation

1. **Check if the libraries are installed**:
   ```bash
   ls /usr/local/lib | grep TK
   ```
   You should see Open CASCADE libraries like `TKDraw`, `TKG2d`, etc.

2. **Test the installation**:
   Run example programs (if available) or your custom scripts to validate the installation.



## Optional Notes

- **TCL/TK Issues**:
  If `TCL/TK` headers are not detected, verify their paths and rerun CMake:
  ```bash
  cmake .. -DTCL_INCLUDE_PATH=/usr/include/tcl8.6 -DTK_INCLUDE_PATH=/usr/include/tk8.6
  ```

- **Git Depth and Buffer Issues**:
  To avoid fetch-related errors, always use a shallow clone and increase the Git buffer size:
  ```bash
  git config --global http.postBuffer 524288000
  git clone --depth 1 https://github.com/Open-Cascade-SAS/OCCT.git
  ```



## Uninstallation

If you need to uninstall Open CASCADE:

```bash
sudo rm -rf /usr/local/lib/libTK*
sudo rm -rf /usr/local/include/OpenCASCADE
```



## Acknowledgments

This guide is based on the official Open CASCADE repository and adapted for installation on Raspberry Pi.


# Saving and Reusing Open CASCADE C Library

If you want to save the built Open CASCADE C library for future use, follow these steps. This method allows you to avoid rebuilding the library every time and quickly install it when needed.



## Saving the Built Library

1. **Locate the Installed Files**:
   After building and installing Open CASCADE, the libraries and headers are typically located under:
   - `/usr/local/lib` for libraries.
   - `/usr/local/include` for headers.

2. **Compress the Installation**:
   Save the libraries and headers as a compressed archive:
   ```bash
   tar -czvf occt-library.tar.gz /usr/local/lib/libTK* /usr/local/include/OpenCASCADE
   ```
   - This creates a file `occt-library.tar.gz` containing:
     - All `libTK*` libraries (e.g., `libTKG2d`, `libTKMath`).
     - The `OpenCASCADE` headers.

3. **Store the Archive**:
   - Save the `occt-library.tar.gz` file in a secure location, such as a USB drive, cloud storage, or a Git repository.



## Reusing or Installing the Library Later

1. **Extract the Saved Archive**:
   When needed, extract the archive to the appropriate location:
   ```bash
   sudo tar -xzvf occt-library.tar.gz -C /
   ```
   - This restores the libraries to `/usr/local/lib` and headers to `/usr/local/include/OpenCASCADE`.

2. **Update the Library Cache**:
   After extracting, update the library cache to ensure the system recognizes the new libraries:
   ```bash
   sudo ldconfig
   ```

3. **Verify the Installation**:
   Check if the libraries are available:
   ```bash
   ls /usr/local/lib | grep TK
   ```
   - This should list all Open CASCADE libraries.



## Advantages of This Method

- **Time-Saving**: Avoids recompilation, especially for large projects.
- **Portability**: You can transfer the library to other devices with the same architecture (e.g., other Raspberry Pi devices).
- **Ease of Use**: Reinstallation is as simple as extracting the archive.



## Additional Notes

- If you plan to use the saved library on a different system, ensure the target system has compatible dependencies, such as:
  - `libx11-dev`
  - `libfreetype6-dev`
  - `libgl1-mesa-dev`, etc.
- Test the library after extraction by compiling a small example to ensure compatibility.
