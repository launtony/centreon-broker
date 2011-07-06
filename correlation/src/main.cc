/*
** Copyright 2011 Merethis
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

#include <QSharedPointer>
#include "com/centreon/broker/config/state.hh"
#include "com/centreon/broker/correlation/correlator.hh"
#include "com/centreon/broker/multiplexing/publisher.hh"

using namespace com::centreon::broker;

// Load count.
static unsigned int instances(0);

// Correlation object.
static QSharedPointer<io::stream> obj;

extern "C" {
  /**
   *  Module deinitialization routine.
   *
   *  @param[in] force true if module unloading is forced (no need to
   *                   cleanup).
   */
  void broker_module_deinit(bool force) {
    // Decrement instance number.
    if (!--instances && !force) {
      // Unregister correlation object.
      multiplexing::publisher::unhook(obj);
      obj.clear();
    }
    return ;
  }

  /**
   *  Module initialization routine.
   *
   *  @param[in] arg Configuration argument.
   */
  void broker_module_init(void const* arg) {
    // Increment instance number.
    if (!instances++) {
      // Check that correlation is enabled.
      config::state const& cfg(*static_cast<config::state const*>(arg));
      QMap<QString, QString>::const_iterator
        it(cfg.params().find("correlation"));
      if (it != cfg.params().end()) {
        // Create and register correlation object.
        QSharedPointer<correlation::correlator>
          crltr(new correlation::correlator);
        crltr->load(it.value());
        obj = crltr.staticCast<io::stream>();
        multiplexing::publisher::hook(obj);
      }
    }
    return ;
  }
}