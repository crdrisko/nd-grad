// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variant.hpp
// Author: crdrisko
// Date: 01/01/2021-07:05:20
// Description: The main Variant class template

#ifndef VARIANT_HPP
#define VARIANT_HPP

#include "variantchoice.hpp"
#include "variantstorage.hpp"

template<typename... Types>
class Variant : private VariantStorage<Types...>, private VariantChoice<Types, Types...>...
{
    template<typename T, typename... OtherTypes>
    friend class VariantChoice;

public:
    template<typename T> bool is() const;                   // see variantis.hpp

    template<typename T> T& get() &;                        // see variantget.hpp
    template<typename T> T const& get() const&;             // see variantget.hpp
    template<typename T> T&& get() &&;                      // see variantget.hpp

    // see variantvisit.hpp:
    template<typename R = ComputedResultType, typename Visitor>
    VisitResult<R, Visitor, Types&...> visit(Visitor&& vis) &;

    template<typename R = ComputedResultType, typename Visitor>
    VisitResult<R, Visitor, Types const&...> visit(Visitor&& vis) const&;

    template<typename R = ComputedResultType, typename Visitor>
    VisitResult<R, Visitor, Types&&...> visit(Visitor&& vis) &&;

    using VariantChoice<Types, Types...>::VariantChoice...;

    Variant();                                              // see variantdefaultctor.hpp
    Variance(Variant const& source);                        // see variantcopyctor.hpp
    Variance(Variant&& source);                             // see variantmovectpr.hpp

    template<typename... SourceTypes>
    Variant(Variant<SourceTypes...> const& source);         // see variantcopyctortmpl.hpp

    template<typename... SourceTypes>
    Variant(Variant<SourceTypes...>&& source);

    using VariantChoice<Types, Types...>::operator=...;

    Variant& operator=(Variant const& source);              // see variantcopyassign.hpp
    Variant& operator=(Variant&& source);

    template<typename... SourceTypes>
    Variant& operator=(Variant<SourceTypes...> const& source);

    template<typename... SourceTypes>
    Variant& operator=(Variant<SourceTypes...>&& source);


    bool empty() const;

    ~Variant() { destroy(); }
    void destroy();                                         // see variantdestroy.hpp
};

#endif
