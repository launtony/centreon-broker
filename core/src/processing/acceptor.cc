/*
** Copyright 2015 Merethis
**
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

#include <QMutexLocker>
#include <sstream>
#include "com/centreon/broker/logging/logging.hh"
#include "com/centreon/broker/multiplexing/publisher.hh"
#include "com/centreon/broker/multiplexing/subscriber.hh"
#include "com/centreon/broker/processing/acceptor.hh"
#include "com/centreon/broker/processing/feeder.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::processing;

/**
 *  Constructor.
 *
 *  @param[in] endp       Endpoint.
 *  @param[in] in_or_out  Either in or out to determine how the clients
 *                        should be constructed.
 *  @param[in] name       Name of the endpoint.
 */
acceptor::acceptor(
            misc::shared_ptr<io::endpoint> endp,
            acceptor::in_out in_or_out,
            std::string const& name)
  : _endp(endp),
    _in_out(in_or_out),
    _name(name),
    _retry_interval(30) {}

/**
 *  Destructor.
 */
acceptor::~acceptor() {
  _wait_feeders();
}

/**
 *  Accept a new incoming connection.
 */
void acceptor::accept() {
  // Try to accept connection.
  misc::shared_ptr<io::stream> s(_endp->open());
  if (!s.isNull()) {
    // Create feeder thread.
    misc::shared_ptr<processing::feeder>
      f(new processing::feeder);
    std::ostringstream name;
    name << _name << "-" << f.data();
    if (_in_out == out) {
      misc::shared_ptr<multiplexing::subscriber>
        sbscrbr(new multiplexing::subscriber(name.str().c_str()));
      sbscrbr->set_filters(_filters);
      f->prepare(name.str(), sbscrbr, s);
    }
    else {
      misc::shared_ptr<multiplexing::publisher>
        pblshr(new multiplexing::publisher);
      f->prepare(name.str(), s, pblshr);
    }

    // Run feeder thread.
    f->start();
    _feeders.push_back(f);
  }
  return ;
}

/**
 *  Exit this thread.
 */
void acceptor::exit() {
  thread::exit();
  _endp->close();
  return ;
}

/**
 *  @brief Main routine.
 *
 *  Acceptors accepts clients and launch feeder threads.
 */
void acceptor::run() {
  // Run as long as no exit request was made.
  while (!should_exit()) {
    try {
      // Try to accept connection.
      accept();
    }
    catch (std::exception const& e) {
      // Log error.
      logging::error(logging::high) << "acceptor: endpoint '"
        << _name << "' could not accept client: " << e.what();

      // Sleep a while before reconnection.
      // XXX
    }

    // Check for terminated feeders.
    for (std::list<misc::shared_ptr<processing::feeder> >::iterator
           it(_feeders.begin()),
           end(_feeders.end());
         it != end;)
      if ((*it)->wait(0))
        it = _feeders.erase(it);
      else
        ++it;
  }

  // Cleanup.
  _wait_feeders();

  return ;
}

/**
 *  @brief Set event filters.
 *
 *  This is only useful in input mode.
 *
 *  @param[in] filters  Set of accepted event IDs.
 */
void acceptor::set_filters(std::set<unsigned int> const& filters) {
  _filters = filters;
  return ;
}

/**
 *  @brief Set retry interval of the acceptor.
 *
 *  The retry interval is only used in case of error of the acceptor. In
 *  normal operation mode, connections are accepted as soon as possible.
 *
 *  @param[in] retry_interval  Retry interval between two client
 *                             acception attempts in case of error at
 *                             the first attempt.
 */
void acceptor::set_retry_interval(time_t retry_interval) {
  _retry_interval = retry_interval;
  return ;
}

/**
 *  Wait for launched feeders.
 */
void acceptor::_wait_feeders() {
  // Wait for all launched feeders.
  for (std::list<misc::shared_ptr<processing::feeder> >::iterator
         it(_feeders.begin()),
         end(_feeders.end());
       it != end;
       ++it)
    (*it)->exit();
  for (std::list<misc::shared_ptr<processing::feeder> >::iterator
         it(_feeders.begin()),
         end(_feeders.end());
       it != end;
       ++it)
    (*it)->wait();
  _feeders.clear();
  return ;
}