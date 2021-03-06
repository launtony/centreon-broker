/*
** Copyright 2015 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#ifndef CCB_WATCHDOG_INSTANCE_HH
#  define CCB_WATCHDOG_INSTANCE_HH

#  include <QObject>
#  include <QProcess>
#  include <string>
#  include "com/centreon/broker/timestamp.hh"
#  include "com/centreon/broker/watchdog/instance_configuration.hh"
#  include "com/centreon/broker/namespace.hh"

namespace               com {
  namespace             centreon {
    namespace           broker {
      namespace         watchdog {
      class application;

  /**
   *  @class instance instance.hh "com/centreon/broker/watchdog/instance.hh"
   *  @brief This represents the process associated with an instance of broker.
   */
        class           instance : public QProcess {
          Q_OBJECT
        public:
                        instance(
                          instance_configuration const& config,
                          application& parent);
                        ~instance();

          void          merge_configuration(
                          instance_configuration const& new_config);

        public slots:
          void          start_instance();
          void          update_instance();
          void          stop_instance();

        public slots:
          void          on_exit();

        private:
                        instance(instance const&);
          instance& operator=(
                        instance const&);

          instance_configuration
                        _config;
          bool          _started;
          timestamp     _since_last_start;
        };
      }
    }
  }
}

#endif // !CCB_WATCHDOG_INSTANCE_HH
