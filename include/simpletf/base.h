#pragma once

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/log/log.h"

namespace simpletf {

using Status = absl::Status;
using StatusCode = absl::StatusCode;
template <typename T>
using StatusOr = absl::StatusOr<T>;

} // namespace simpletf