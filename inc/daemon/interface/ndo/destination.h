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

#ifndef INTERFACE_NDO_DESTINATION_H_
# define INTERFACE_NDO_DESTINATION_H_

# include <memory>                  // for auto_ptr
# include "interface/destination.h"

// Forward declaration.
namespace          IO
{ class            Stream; }

namespace          Interface
{
  namespace        NDO
  {
    /**
     *  \class Destination destination.h "interface/ndo/destination.h"
     *  \brief NDO destination output.
     *
     *  The Interface::NDO::Destination class converts events to an output
     *  stream using the NDO protocol.
     */
    class          Destination : public Interface::Destination
    {
     private:
      std::auto_ptr<IO::Stream>
                   stream_;
                   Destination(const Destination& dest);
      Destination& operator=(const Destination& dest);

     public:
                   Destination(IO::Stream* stream);
      virtual      ~Destination();
      virtual void Close();
      virtual void Event(const Events::Event& event);
      static void  Initialize();
    };
  }
}

#endif /* !INTERFACE_NDO_DESTINATION_H_ */