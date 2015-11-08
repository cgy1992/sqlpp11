/*
 * Copyright (c) 2013-2015, Roland Bock
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

#ifndef SQLPP_OPERATORS_H
#define SQLPP_OPERATORS_H

#include <sqlpp11/wrap_operand.h>
#include <sqlpp11/expression_return_types.h>

namespace sqlpp
{
  template <typename L, typename R>
  auto operator and(const L& l, const R& r) -> return_type_and_t<L, R>
  {
    return_type_and<L, R>::check::_();
    return {wrap_operand_t<L>{l}, wrap_operand_t<R>{r}};
  }
  template <typename L, typename R>
  auto operator or(const L& l, const R& r) -> return_type_or_t<L, R>
  {
    return_type_or<L, R>::check::_();
    return {wrap_operand_t<L>{l}, wrap_operand_t<R>{r}};
  }
  template <typename T>
  auto operator not(const T& t) -> return_type_not_t<T>
  {
    return_type_not<T>::check::_();
    return {wrap_operand_t<T>{t}};
  }
}

#endif