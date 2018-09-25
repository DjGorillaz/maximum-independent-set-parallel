#pragma once

template <
           typename Iter,
           typename Func
         >
constexpr void visit_variant(Iter begin, Iter end, Func&& func)
{
    for (auto it = begin; it != end; ++it)
        std::visit(std::forward<Func>(func), *it);
}
