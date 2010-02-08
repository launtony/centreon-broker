/*
**  Copyright 2009 MERETHIS
**  This file is part of CentreonBroker.
**
**  CentreonBroker is free software: you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the Free
**  Software Foundation, either version 2 of the License, or (at your option)
**  any later version.
**
**  CentreonBroker is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
**  for more details.
**
**  You should have received a copy of the GNU General Public License along
**  with CentreonBroker.  If not, see <http://www.gnu.org/licenses/>.
**
**  For more information : contact@centreon.com
*/

#ifndef DB_QUERY_H_
# define DB_QUERY_H_

namespace          CentreonBroker
{
  namespace        DB
  {
    class          Query
    {
     protected:
                   Query() throw ();
                   Query(const Query& query) throw ();
      Query&       operator=(const Query& query) throw ();

     public:
      virtual      ~Query();
      virtual void Execute() = 0;
      virtual void Prepare() = 0;
    };
  }
}

#endif /* !DB_QUERY_H_ */