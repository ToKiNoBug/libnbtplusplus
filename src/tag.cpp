/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "tag.h"
#include <ostream>
#include <typeinfo>

namespace nbt
{

std::unique_ptr<tag> tag::clone() &&
{
    return std::move(*this).move_clone();
}

bool operator==(const tag& lhs, const tag& rhs)
{
    if(typeid(lhs) != typeid(rhs))
        return false;
    return lhs.equals(rhs);
}

bool operator!=(const tag& lhs, const tag& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, tag_type tt)
{
    switch(tt)
    {
    case tag_type::End:         return os << "end";
    case tag_type::Byte:        return os << "byte";
    case tag_type::Short:       return os << "short";
    case tag_type::Int:         return os << "int";
    case tag_type::Long:        return os << "long";
    case tag_type::Float:       return os << "float";
    case tag_type::Double:      return os << "double";
    case tag_type::Byte_Array:  return os << "byte_array";
    case tag_type::List:        return os << "list";
    case tag_type::Compound:    return os << "compound";
    case tag_type::Int_Array:   return os << "int_array";
    case tag_type::Null:        return os << "null";

    default:                    return os << "invalid";
    }
}

}
