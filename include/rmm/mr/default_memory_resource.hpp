/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "device_memory_resource.hpp"

#include <vector>
namespace rmm {
namespace mr {

/**---------------------------------------------------------------------------*
 * @brief Get the default device memory resource pointer.
 *
 * The default device memory resource is used when an explicit memory resource
 * is not supplied. The initial default memory resource is a
 * `cuda_memory_resource`.
 *
 * This function is thread-safe.
 *
 * @return device_memory_resource* Pointer to the current default memory
 * resource
 *---------------------------------------------------------------------------**/
device_memory_resource* get_default_resource();

/**---------------------------------------------------------------------------*
 * @brief Sets the default device memory resource pointer.
 *
 * If `new_resource` is not `nullptr`, sets the default device memory resource
 * pointer to `new_resource`. Otherwise, resets the default device memory
 * resource to the initial `cuda_memory_resource`.
 *
 * It is the caller's responsibility to maintain the lifetime of the object
 * pointed to by `new_resource`.
 *
 * This function is thread-safe.
 *
 * @param new_resource If not nullptr, pointer to memory resource to use as new
 * default device memory resource
 * @return device_memory_resource* The previous value of the default device
 * memory resource pointer
 *---------------------------------------------------------------------------**/
device_memory_resource* set_default_resource(
    device_memory_resource* new_resource);

namespace detail {

/**---------------------------------------------------------------------------*
 * @brief gets the default memory_resource when none is set
 *
 * A static function which will return a singleton cuda_memory_resource
 *
 *
 * @return device_memory_resource* a pointer to the static
 * cuda_memory_resource
 *---------------------------------------------------------------------------**/
device_memory_resource* initial_resource();

/**---------------------------------------------------------------------------*
 * @brief gets a cuda_memory_resource
 *
 * A static function which will return a singleton cuda_memory_resource
 *
 *
 *
 * @return device_memory_resource* a pointer to the static
 * cuda_memory_resource
 *---------------------------------------------------------------------------**/
device_memory_resource* cuda_resource();

/**---------------------------------------------------------------------------*
 * @brief gets a cnmem_memory_resource
 *
 * A static function which will return a singleton cnmem_memory_resource which
 * manages a pool
 *
 *
 * @param pool_size The initial size of the pool
 * @return device_memory_resource* a pointer to the static
 * cnmem_memory_resource
 *---------------------------------------------------------------------------**/
device_memory_resource* pool_resource(std::size_t pool_size = 0,
                                      std::vector<int> const& devices = {});

/**---------------------------------------------------------------------------*
 * @brief gets a cnmem_managed_memory_resource
 *
 * A static function which will return a singleton cnmem_memory_resource which
 * manages a pool of UVM memory
 *
 * @param pool_size The initial size of the pool
 * @return device_memory_resource* a pointer to the static
 * cnmem_managed_memory_resource
 *---------------------------------------------------------------------------**/
device_memory_resource* managed_pool_resource(
    std::size_t pool_size = 0, std::vector<int> const& devices = {});

/**---------------------------------------------------------------------------*
 * @brief gets a managed_memory_resource
 *
 * A static function that returns a singleton managed_memory_resource.
 *
 *
 *
 * @return device_memory_resource* a pointer to the static
 * managed_memory_resource
 *---------------------------------------------------------------------------**/
device_memory_resource* managed_resource();
}  // namespace detail
}  // namespace mr
}  // namespace rmm
