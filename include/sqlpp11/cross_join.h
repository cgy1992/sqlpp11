/*
 * Copyright (c) 2013-2016, Roland Bock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SQLPP_CROSS_JOIN_H
#define SQLPP_CROSS_JOIN_H

#include <sqlpp11/join_types.h>
#include <sqlpp11/on.h>
#include <sqlpp11/noop.h>

namespace sqlpp
{
  template <typename CrossJoin, typename On>
  struct join_t;

  template <typename JoinType, typename Lhs, typename Rhs>
  struct cross_join_t
  {
    using _traits = make_traits<no_value_t, tag::is_cross_join>;
    using _nodes = detail::type_vector<Lhs, Rhs>;
    using _can_be_null = std::false_type;

    static_assert(is_table_t<Lhs>::value, "lhs argument for join() has to be a table or join");
    static_assert(is_table_t<Rhs>::value, "rhs argument for join() has to be a table");
    static_assert(not is_join_t<Rhs>::value, "rhs argument for join must not be a join");

    static_assert(detail::is_disjunct_from<provided_tables_of<Lhs>, provided_tables_of<Rhs>>::value,
                  "joined tables must not be identical");

    static_assert(required_tables_of<cross_join_t>::size::value == 0, "joined tables must not depend on other tables");

    template <typename Expr>
    auto on(Expr expr) -> join_t<cross_join_t, on_t<void, Expr>>
    {
      static_assert(is_expression_t<Expr>::value, "argument is not an expression in on()");

      static_assert(is_boolean_t<Expr>::value, "argument is not a boolean expression in on()");

      return {*this, {expr, {}}};
    }

    auto unconditionally() -> join_t<cross_join_t, on_t<void, unconditional_t>>
    {
      return {*this, {}};
    }

    Lhs _lhs;
    Rhs _rhs;
  };

  template <typename Context, typename JoinType, typename Lhs, typename Rhs>
  struct serializer_t<Context, cross_join_t<JoinType, Lhs, Rhs>>
  {
    using _serialize_check = serialize_check_of<Context, Lhs, Rhs>;
    using T = cross_join_t<JoinType, Lhs, Rhs>;

    static Context& _(const T& t, Context& context)
    {
      serialize(t._lhs, context);
      context << JoinType::_name;
      context << " JOIN ";
      serialize(t._rhs, context);
      return context;
    }
  };
}

#endif