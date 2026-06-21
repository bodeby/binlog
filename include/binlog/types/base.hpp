//

#pragma once

#include <ostream>
namespace binlog {

template <typename T, typename Tag> class BaseType {
  public:
    using value_type = T;

    constexpr BaseType() noexcept = default;
    constexpr explicit BaseType(T value) noexcept : value_(value) {}

    [[nodiscard]]
    constexpr auto raw() const noexcept -> T {
        return value_;
    }
    constexpr auto operator==(const BaseType&) const noexcept -> bool = default;
    constexpr auto operator<=>(const BaseType&) const noexcept = default;

  private:
    T value_{};
};

template <typename T, typename Tag>
auto operator<<(std::ostream& os, const BaseType<T, Tag>& value) -> std::ostream& {
    return os << value.raw();
}

template <typename T, typename U> constexpr auto validateBaseType() noexcept -> bool {
    static_assert(std::is_trivially_copyable_v<T>);
    static_assert(std::is_standard_layout_v<T>);
    static_assert(sizeof(T) == sizeof(U));
    return true;
}

} // namespace binlog

namespace std {

template <typename T, typename Tag> struct hash<binlog::BaseType<T, Tag>> {
    auto operator()(const binlog::BaseType<T, Tag>& value) const noexcept -> std::size_t {
        return std::hash<T>{}(value.raw());
    }
};

} // namespace std
