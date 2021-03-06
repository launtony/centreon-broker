/*
** Copyright 2014-2015 Centreon
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

#ifndef CCB_BAM_BA_HH
#  define CCB_BAM_BA_HH

#  include <string>
#  include <vector>
#  include "com/centreon/broker/bam/ba_event.hh"
#  include "com/centreon/broker/bam/ba_duration_event.hh"
#  include "com/centreon/broker/bam/computable.hh"
#  include "com/centreon/broker/bam/impact_values.hh"
#  include "com/centreon/broker/bam/service_listener.hh"
#  include "com/centreon/broker/io/stream.hh"
#  include "com/centreon/broker/misc/shared_ptr.hh"
#  include "com/centreon/broker/misc/unordered_hash.hh"
#  include "com/centreon/broker/namespace.hh"

CCB_BEGIN()

namespace        bam {
  // Forward declaration.
  class          kpi;

  /**
   *  @class ba ba.hh "com/centreon/broker/bam/ba.hh"
   *  @brief Business activity.
   *
   *  Represents a BA that gets computed every time an impact change
   *  of value.
   */
  class          ba : public computable, public service_listener {
  public:
                 ba(bool generate_virtual_status = true);
                 ba(ba const& other);
                 ~ba();
    ba&          operator=(ba const& other);
    void         add_impact(misc::shared_ptr<kpi> const& impact);
    bool         child_has_update(
                   computable* child,
                   io::stream* visitor = NULL);
    double       get_ack_impact_hard();
    double       get_ack_impact_soft();
    ba_event*    get_ba_event();
    double       get_downtime_impact_hard();
    double       get_downtime_impact_soft();
    unsigned int get_id();
    unsigned int get_host_id() const;
    unsigned int get_service_id() const;
    bool         get_in_downtime() const;
    timestamp    get_last_kpi_update() const;
    std::string const&
                 get_name() const;
    std::string  get_output() const;
    std::string  get_perfdata() const;
    short        get_state_hard();
    short        get_state_soft();
    void         remove_impact(misc::shared_ptr<kpi> const& impact);
    void         set_id(unsigned int id);
    void         set_host_id(unsigned int host_id);
    void         set_service_id(unsigned int service_id);
    void         set_level_critical(double level);
    void         set_level_warning(double level);
    void         set_initial_event(ba_event const& event);
    void         set_name(std::string const& name);
    void         set_valid(bool valid);
    void         visit(io::stream* visitor);
    void         service_update(
                   misc::shared_ptr<neb::downtime> const& dt,
                   io::stream* visitor);

  private:
    static int const        _recompute_limit = 100;

    struct impact_info {
      misc::shared_ptr<kpi> kpi_ptr;
      impact_values         hard_impact;
      impact_values         soft_impact;
    };

    void         _apply_impact(impact_info& impact);
    void         _internal_copy(ba const& other);
    void         _open_new_event(
                   io::stream* visitor,
                   short service_hard_state);
    void         _recompute();
    void         _unapply_impact(impact_info& impact);

    double       _acknowledgement_hard;
    double       _acknowledgement_soft;
    double       _downtime_hard;
    double       _downtime_soft;
    misc::shared_ptr<ba_event>
                 _event;
    bool         _generate_virtual_status;
    unsigned int _host_id;
    unsigned int _id;
    umap<kpi*, impact_info>
                 _impacts;
    bool         _in_downtime;
    timestamp    _last_kpi_update;
    double       _level_critical;
    double       _level_hard;
    double       _level_soft;
    double       _level_warning;
    std::string  _name;
    int          _recompute_count;
    unsigned int _service_id;
    bool         _valid;

    void         _commit_initial_events(io::stream* visitor);

    std::vector<misc::shared_ptr<ba_event> >
                 _initial_events;
  };
}

CCB_END()

#endif // !CCB_BAM_BA_HH
