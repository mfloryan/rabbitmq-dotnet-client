#include <stdint.h>

#include "nvim/vim.h"
#include "nvim/map.h"
#include "nvim/api/private/handle.h"

#define HANDLE_INIT(name) name##_handles = map_new(uint64_t)()

#define HANDLE_IMPL(type, name)                                               \
  static Map(uint64_t) *name##_handles = NULL;                                \
                                                                              \
  type *handle_get_##name(uint64_t handle)                                    \
  {                                                                           \
    return map_get(uint64_t)(name##_handles, handle);                         \
  }                                                                           \
                                                                              \
  void handle_register_##name(type *name)                                     \
  {                                                                           \
    assert(!name->handle);                                                    \
    name->handle = next_handle++;                                             \
    map_put(uint64_t)(name##_handles, name->handle, name);                    \
  }                                                                           \
                                                                              \
  void handle_unregister_##name(type *name)                                   \
  {                                                                           \
    map_del(uint64_t)(name##_handles, name->handle);                          \
  }

void handle_init()
{
}
