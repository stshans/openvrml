// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2006, 2007, 2008, 2009  Braden McDaniel
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# include "receiver_pdu.h"
# include <openvrml/node_impl_util.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

using namespace openvrml;
using namespace openvrml::node_impl_util;
using namespace std;

namespace {

    /**
     * @brief Represents ReceiverPdu node instances.
     */
    class OPENVRML_LOCAL receiver_pdu_node :
        public abstract_node<receiver_pdu_node>,
        public child_node {

        friend class openvrml_node_x3d_dis::receiver_pdu_metatype;

        exposedfield<sfstring> address_;
        exposedfield<sfint32> application_id_;
        exposedfield<sfint32> entity_id_;
        exposedfield<sfstring> multicast_relay_host_;
        exposedfield<sfint32> multicast_relay_port_;
        exposedfield<sfstring> network_mode_;
        exposedfield<sfint32> port_;
        exposedfield<sfint32> radio_id_;
        exposedfield<sffloat> read_interval_;
        exposedfield<sffloat> received_power_;
        exposedfield<sfint32> receiver_state_;
        exposedfield<sfbool> rtp_header_expected_;
        exposedfield<sfint32> site_id_;
        exposedfield<sfint32> transmitter_application_id_;
        exposedfield<sfint32> transmitter_entity_id_;
        exposedfield<sfint32> transmitter_radio_id_;
        exposedfield<sfint32> transmitter_site_id_;
        exposedfield<sfint32> which_geometry_;
        exposedfield<sffloat> write_interval_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfbool is_network_reader_;
        sfbool_emitter is_network_reader_emitter_;
        sfbool is_network_writer_;
        sfbool_emitter is_network_writer_emitter_;
        sfbool is_rtp_header_heard_;
        sfbool_emitter is_rtp_header_heard_emitter_;
        sfbool is_stand_alone_;
        sfbool_emitter is_stand_alone_emitter_;
        sftime timestamp_;
        sftime_emitter timestamp_emitter_;
        sfvec3f bbox_center_;
        sfvec3f bbox_size_;

    public:
        receiver_pdu_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~receiver_pdu_node() OPENVRML_NOTHROW;
    };


    /**
     * @var receiver_pdu_node::receiver_pdu_metatype
     *
     * @brief Class object for ReceiverPdu nodes.
     */

    /**
     * @var receiver_pdu_node::address_
     *
     * @brief address exposedField
     */

    /**
     * @var receiver_pdu_node::application_id_
     *
     * @brief application_id exposedField
     */

    /**
     * @var receiver_pdu_node::entity_id_
     *
     * @brief entity_id exposedField
     */

    /**
     * @var receiver_pdu_node::multicast_relay_host_
     *
     * @brief multicast_relay_host exposedField
     */

    /**
     * @var receiver_pdu_node::multicast_relay_port_
     *
     * @brief multicast_relay_port exposedField
     */

    /**
     * @var receiver_pdu_node::network_mode_
     *
     * @brief network_mode exposedField
     */

    /**
     * @var receiver_pdu_node::port_
     *
     * @brief port exposedField
     */

    /**
     * @var receiver_pdu_node::radio_id_
     *
     * @brief radio_id exposedField
     */

    /**
     * @var receiver_pdu_node::read_interval_
     *
     * @brief read_interval exposedField
     */

    /**
     * @var receiver_pdu_node::received_power_
     *
     * @brief received_power exposedField
     */

    /**
     * @var receiver_pdu_node::receiver_state_
     *
     * @brief receiver_state exposedField
     */

    /**
     * @var receiver_pdu_node::rtp_header_expected_
     *
     * @brief rtp_header_expected exposedField
     */

    /**
     * @var receiver_pdu_node::site_id_
     *
     * @brief site_id exposedField
     */

    /**
     * @var receiver_pdu_node::transmitter_application_id_
     *
     * @brief transmitter_application_id exposedField
     */

    /**
     * @var receiver_pdu_node::transmitter_entity_id_
     *
     * @brief transmitter_entity_id exposedField
     */

    /**
     * @var receiver_pdu_node::transmitter_radio_id_
     *
     * @brief transmitter_radio_id exposedField
     */

    /**
     * @var receiver_pdu_node::transmitter_site_id_
     *
     * @brief transmitter_site_id exposedField
     */

    /**
     * @var receiver_pdu_node::which_geometry_
     *
     * @brief which_geometry exposedField
     */

    /**
     * @var receiver_pdu_node::write_interval_
     *
     * @brief write_interval exposedField
     */

    /**
     * @var receiver_pdu_node::is_active_
     *
     * @brief is_active eventOut
     */

    /**
     * @var receiver_pdu_node::is_network_reader_
     *
     * @brief is_network_reader eventOut
     */

    /**
     * @var receiver_pdu_node::is_network_writer_
     *
     * @brief is_network_writer eventOut
     */

    /**
     * @var receiver_pdu_node::is_rtp_header_heard_
     *
     * @brief is_rtp_header_heard eventOut
     */

    /**
     * @var receiver_pdu_node::is_stand_alone_
     *
     * @brief is_stand_alone eventOut
     */

    /**
     * @var receiver_pdu_node::timestamp_
     *
     * @brief timestamp eventOut
     */

    /**
     * @var receiver_pdu_node::bbox_center_
     *
     * @brief bbox_center field
     */

    /**
     * @var receiver_pdu_node::bbox_size_
     *
     * @brief bbox_size field
     */


    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope     the scope to which the node belongs.
     */
    receiver_pdu_node::
    receiver_pdu_node(const node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<self_t>(type, scope),
        child_node(type, scope),
        address_(*this, "localhost"),
        application_id_(*this, 1),
        entity_id_(*this),
        multicast_relay_host_(*this),
        multicast_relay_port_(*this),
        network_mode_(*this, "standAlone"),
        port_(*this),
        radio_id_(*this),
        read_interval_(*this, 0.1f),
        received_power_(*this),
        receiver_state_(*this),
        rtp_header_expected_(*this),
        site_id_(*this),
        transmitter_application_id_(*this, 1),
        transmitter_entity_id_(*this),
        transmitter_radio_id_(*this),
        transmitter_site_id_(*this),
        which_geometry_(*this, 1),
        write_interval_(*this, 1),
        is_active_emitter_(*this, this->is_active_),
        is_network_reader_emitter_(*this, this->is_network_reader_),
        is_network_writer_emitter_(*this, this->is_network_writer_),
        is_rtp_header_heard_emitter_(*this, this->is_rtp_header_heard_),
        is_stand_alone_emitter_(*this, this->is_stand_alone_),
        timestamp_emitter_(*this, this->timestamp_),
        bbox_size_(make_vec3f(-1.0f, -1.0f, -1.0f))
    {}

    /**
     * @brief Destroy.
     */
    receiver_pdu_node::~receiver_pdu_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_x3d_dis::receiver_pdu_metatype::id =
    "urn:X-openvrml:node:ReceiverPdu";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this
 *                @c receiver_pdu_metatype.
 */
openvrml_node_x3d_dis::receiver_pdu_metatype::
receiver_pdu_metatype(openvrml::browser & browser):
    node_metatype(receiver_pdu_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_dis::receiver_pdu_metatype::~receiver_pdu_metatype()
    OPENVRML_NOTHROW
{}

# define RECEIVER_PDU_INTERFACE_SEQ                                     \
    ((exposedfield, sfnode,   "metadata",                 metadata))    \
    ((exposedfield, sfstring, "address",                  address_))    \
    ((exposedfield, sfint32,  "applicationID",            application_id_)) \
    ((exposedfield, sfint32,  "entityID",                 entity_id_))  \
    ((exposedfield, sfstring, "multicastRelayHost",       multicast_relay_host_)) \
    ((exposedfield, sfint32,  "multicastRelayPort",       multicast_relay_port_)) \
    ((exposedfield, sfstring, "networkMode",              network_mode_)) \
    ((exposedfield, sfint32,  "port",                     port_))       \
    ((exposedfield, sfint32,  "radioID",                  radio_id_))   \
    ((exposedfield, sffloat,  "readInterval",             read_interval_)) \
    ((exposedfield, sffloat,  "receivedPower",            received_power_)) \
    ((exposedfield, sfint32,  "receiverState",            receiver_state_)) \
    ((exposedfield, sfbool,   "rtpHeaderExpected",        rtp_header_expected_)) \
    ((exposedfield, sfint32,  "siteID",                   site_id_))    \
    ((exposedfield, sfint32,  "transmitterApplicationID", transmitter_application_id_)) \
    ((exposedfield, sfint32,  "transmitterEntityID",      transmitter_entity_id_)) \
    ((exposedfield, sfint32,  "transmitterRadioID",       transmitter_radio_id_)) \
    ((exposedfield, sfint32,  "transmitterSiteID",        transmitter_site_id_)) \
    ((exposedfield, sfint32,  "whichGeometry",            which_geometry_)) \
    ((exposedfield, sffloat,  "writeInterval",            write_interval_)) \
    ((eventout,     sfbool,   "isActive",                 is_active_emitter_)) \
    ((eventout,     sfbool,   "isNetworkReader",          is_network_reader_emitter_)) \
    ((eventout,     sfbool,   "isNetworkWriter",          is_network_writer_emitter_)) \
    ((eventout,     sfbool,   "isRtpHeaderHeard",         is_rtp_header_heard_emitter_)) \
    ((eventout,     sfbool,   "isStandAlone",             is_stand_alone_emitter_)) \
    ((eventout,     sftime,   "timestamp",                timestamp_emitter_)) \
    ((field,        sfvec3f,  "bboxCenter",               bbox_center_)) \
    ((field,        sfvec3f,  "bboxSize",                 bbox_size_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_x3d_dis,
                                              receiver_pdu_metatype,
                                              receiver_pdu_node,
                                              RECEIVER_PDU_INTERFACE_SEQ)
