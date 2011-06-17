/*
** Copyright 2009-2011 Merethis
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
*/

#ifndef CCB_MAPPING_HH_
# define CCB_MAPPING_HH_

# include <QString>
# include "events/events.hh"

namespace              com {
  namespace            centreon {
    namespace          broker {
      /**
       *  Holds a pointer to member.
       */
      template         <typename T>
      union            data_member {
        bool           T::*b;
        double         T::*d;
        int            T::*i;
        short          T::*s;
        QString        T::*S;
        time_t         T::*t;
      };

      /**
       *  @class mapped_data mapping.hh "mapping.hh"
       *  @brief Mapping of a data member.
       *
       *  This template represents the overall mapping of a specific
       *  data member of a class T. This data member is associated with
       *  a name (used by DB and XML) and an ID (used by NDO).
       */
      template         <typename T>
      class            mapped_data {
       public:
        enum           Type {
          UNKNOWN = '\0',
          BOOL = 'b',
          DOUBLE = 'd',
          ID = 'I',
          INT = 'i',
          SHORT = 's',
          STRING = 'S',
          TIME_T = 't'
        };
        unsigned int   id;
        data_member<T> member;
        char const*    name;
        char           type;

                       mapped_data() : id(0), name(NULL), type(UNKNOWN) {}

                       mapped_data(bool T::* b, unsigned int i, char const* n)
          : id(i), name(n), type(BOOL)
      { member.b = b; }

                       mapped_data(double T::* d,
                         unsigned int i,
                         char const* n)
          : id(i), name(n), type(DOUBLE)
        { member.d = d; }

                       mapped_data(int T::* I,
                         unsigned int i,
                         char const* n,
                         bool is_id = false)
          : id(i), name(n), type(is_id ? ID : INT)
        { member.i = I; }

                       mapped_data(short T::* s,
                         unsigned int i,
                         char const* n)
          : id(i), name(n), type(SHORT)
        { member.s = s; }

                       mapped_data(QString T::* S,
                         unsigned int i,
                         char const* n)
          : id(i), name(n), type(STRING)
        { member.S = S; }

                       mapped_data(time_t T::* t,
                         unsigned int i,
                         char const* n)
          : id(i), name(n), type(TIME_T)
        { member.t = t; }
      };

      template                       <typename T>
      struct                         mapped_type {
        static mapped_data<T> const* members;
        static char const*           table;
      };
    }
  }
}

#endif /* !CCB_MAPPING_HH_ */