/*
** Copyright 2011-2014 Merethis
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

#ifndef CCB_NOTIFICATION_STATE_HH
#  define CCB_NOTIFICATION_STATE_HH

#  include <ctime>
#  include <memory>
#  include <QSet>
#  include <QPair>
#  include <QSqlDatabase>
#  include <QSqlQuery>
#  include <QString>
#  include <QVector>
#  include <QReadWriteLock>
#  include "com/centreon/broker/namespace.hh"
#  include "com/centreon/broker/notification/loaders/command_loader.hh"
#  include "com/centreon/broker/notification/loaders/contact_loader.hh"
#  include "com/centreon/broker/notification/loaders/dependency_loader.hh"
#  include "com/centreon/broker/notification/loaders/escalation_loader.hh"
#  include "com/centreon/broker/notification/loaders/node_loader.hh"
#  include "com/centreon/broker/notification/loaders/timeperiod_loader.hh"
#  include "com/centreon/broker/notification/loaders/acknowledgement_loader.hh"
#  include "com/centreon/broker/notification/loaders/downtime_loader.hh"
#  include "com/centreon/broker/notification/loaders/notification_method_loader.hh"
#  include "com/centreon/broker/notification/builders/node_set_builder.hh"
#  include "com/centreon/broker/notification/notification_scheduler.hh"


CCB_BEGIN()

namespace             notification {
  /**
   *  @class state state.hh "com/centreon/broker/notification/state.hh"
   *  @brief Regroup the objects loaded from the database.
   */
  class               state {
  public:
                      state();
                      state(state const& obj);
    state&            operator=(state const& obj);

    void              update_objects_from_db(QSqlDatabase& centreon_db,
                                             QSqlDatabase& centreon_storage_db);

    std::auto_ptr<QReadLocker>
                      read_lock();
    std::auto_ptr<QWriteLocker>
                      write_lock();

    objects::node::ptr
                      get_node_by_id(objects::node_id);
    objects::node::ptr
                      get_host_from_service(objects::node_id service_id);
    objects::timeperiod::ptr
                      get_timeperiod_by_name(std::string const& name);
    objects::timeperiod::ptr
                      get_timeperiod_by_node(objects::node_id);
    QList<objects::contact::ptr>
                      get_contacts_by_node(objects::node_id id);
    QList<objects::command::ptr>
                      get_host_commands_by_contact(objects::contact::ptr cnt);
    QList<objects::command::ptr>
                      get_service_commands_by_contact(objects::contact::ptr cnt);
    bool              is_node_in_downtime(objects::node_id id);
    bool              has_node_been_acknowledged(objects::node_id id);

  private:
    QSet<objects::node_id>
                      _nodes;
    QHash<objects::node_id, objects::node::ptr>
                      _node_by_id;
    QMultiHash<objects::node_id, unsigned int>
                      _hostgroups_by_node;
    QMultiHash<objects::node_id, unsigned int>
                      _servicegroups_by_node;
    QMultiHash<unsigned int, unsigned int>
                      _servicegroups_by_hostgroup;
    QMultiHash<unsigned int, unsigned int>
                      _parent_hostgroups;
    QMultiHash<objects::node_id, objects::acknowledgement::ptr>
                      _acks;
    QHash<std::string, objects::command::ptr>
                      _commands;
    QHash<std::string, objects::contact::ptr>
                      _contact_by_name;
    QMultiHash<objects::node_id, objects::contact::ptr>
                      _contacts;
    QMultiHash<std::string, objects::contact::ptr>
                      _contact_by_command;
    QMultiHash<objects::contact::ptr, std::string>
                      _host_command_by_contact;
    QMultiHash<objects::contact::ptr, std::string>
                      _service_command_by_contact;
    QMultiHash<objects::node_id, objects::dependency::ptr>
                      _dependency_by_child_id;
    QMultiHash<objects::node_id, objects::dependency::ptr>
                      _dependency_by_parent_id;
    QMultiHash<objects::node_id, objects::downtime::ptr>
                      _downtimes;
    QMultiHash<objects::node_id, objects::escalation::ptr>
                      _escalations;
    QHash<std::string, objects::timeperiod::ptr>
                      _timeperiod_by_name;
    QHash<unsigned int, objects::notification_method::ptr>
                      _notification_methods;

    QReadWriteLock    _state_mutex;
  };
}

CCB_END()

#endif // !CCB_NOTIFICATION_STATE_HH
