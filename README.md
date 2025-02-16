# rdma-core-mummy

[![rdma-core-mummy CI](https://github.com/RDMA-Rust/rdma-core-mummy/actions/workflows/build.yml/badge.svg)](https://github.com/RDMA-Rust/rdma-core-mummy/actions)

rdma-core-mummy is a lightweight wrapper library that provides stable static linking capabilities for RDMA (Remote Direct Memory Access) applications while maintaining runtime compatibility with different OFED versions.

## Overview

When building RDMA applications, directly linking against rdma-core libraries can lead to compatibility issues due to varying `IBVERBS_PRIVATE_@IBVERBS_PABI_VERSION@` between different OFED versions. While rdma-core provides static build options, it requires bundling the entire rdma-core source code, which can be cumbersome.

Furthermore, many Linux distributions do not provide static libraries (*.a) in their rdma-core packages. For example:
- RHEL/CentOS splits RDMA into runtime and development packages, but still only provides dynamic libraries
- Even when installing OFED, static libraries are not included by default

This makes it challenging to create statically linked RDMA applications, especially when portability across different systems is required.

rdma-core-mummy solves these issues by:
- Providing a minimal static library that contains only the necessary symbols
- Dynamically loading the actual RDMA functions at runtime
- Maintaining binary portability across different OFED versions
- Eliminating the need for distribution-provided static libraries

## Features

- Static linking support for:
  - libibverbs (InfiniBand verbs)
  - librdmacm (RDMA Connection Manager)
  - libibumad (InfiniBand User MAD)
- Runtime dynamic loading of RDMA functions
- No dependency on specific `IBVERBS_PRIVATE` versions
- Lightweight alternative to full rdma-core static linking
- Works on distributions without static RDMA libraries

## Requirements

- CMake 3.7 or later 
- C compiler with C99 support
- OFED or rdma-core development environment

## Building

```bash
mkdir build
cd build
cmake ..
make
```

Optional: Build with examples
```bash
cmake -DBUILD_EXAMPLES=ON ..
make
```

## Usage

In CMake Projects

Add rdma-core-mummy to your project:

```cmake
add_subdirectory(path/to/rdma-core-mummy)
target_link_libraries(your_target
    PRIVATE
        ibverbs    # For InfiniBand verbs
        rdmacm     # For RDMA Connection Manager
        ibumad     # For InfiniBand User MAD
)
```

In Your Code

Just include the necessary headers and use RDMA functions normally:
```c
#include <infiniband/verbs.h>
#include <rdma/rdma_cma.h>

int main() {
    // Your RDMA code here
    struct ibv_device **dev_list;
    int num_devices;
    
    dev_list = ibv_get_device_list(&num_devices);
    // ...
    
    return 0;
}
```

## How It Works

rdma-core-mummy uses function pointers and `dlopen` to dynamically load RDMA functions at runtime from the system's installed RDMA libraries. This approach:

- Provides stable symbols for static linking
- Loads actual implementations from the system's RDMA libraries at runtime
- Maintains compatibility across different OFED versions

## Limitations

- Requires the presence of RDMA libraries (`libibverbs.so.1`, etc.) at runtime
- Does not provide complete rdma-core functionality - only commonly used functions
- Not suitable for environments where dynamic loading is not allowed

## Contributing

Contributions are welcome! Please feel free to submit pull requests with:

- Additional function wrappers
- Bug fixes
- Documentation improvements
- Example code
