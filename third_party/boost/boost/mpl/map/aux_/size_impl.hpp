
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: size_impl.hpp 49239 2008-10-10 09:10:26Z agurtovoy $
// $Date: 2008-10-10 17:10:26 +0800 (周五, 10 十月 2008) $
// $Revision: 49239 $

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED