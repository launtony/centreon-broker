/*
** Copyright 2011-2014 Centreon
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

#ifndef CCB_NOTIFICATION_BUILDERS_NODE_BY_NODE_ID_BUILDER_HH
#  define CCB_NOTIFICATION_BUILDERS_NODE_BY_NODE_ID_BUILDER_HH

#  include <QSet>
#  include "com/centreon/broker/namespace.hh"
#  include "com/centreon/broker/notification/objects/node_id.hh"
#  include "com/centreon/broker/notification/builders/node_builder.hh"

CCB_BEGIN()

namespace           notification {
  /**
   *  @class node_set_builder node_set_builder.hh "com/centreon/broker/notification/builders/node_set_builder.hh"
   *  @brief Build the set of node id.
   *
   *  This class build the set of all the node id of the db.
   */
  class             node_by_node_id_builder : public node_builder {
  public:
                    node_by_node_id_builder(
                      QHash<objects::node_id, objects::node::ptr>& map);
    virtual         ~node_by_node_id_builder() {}

    virtual void    add_node(objects::node::ptr node);

  private:
                    node_by_node_id_builder();

    QHash<objects::node_id, objects::node::ptr>&
                    _map;
  };

}

CCB_END()

#endif // !CCB_NOTIFICATION_BUILDERS_NODE_BY_NODE_ID_BUILDER_HH
