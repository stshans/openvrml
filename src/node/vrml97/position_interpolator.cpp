// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007  Braden McDaniel
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

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

# include <boost/array.hpp>
# include <openvrml/node_impl_util.h>
# include <private.h>
# include "position_interpolator.h"

namespace {

    class OPENVRML_LOCAL position_interpolator_node :
        public openvrml::node_impl_util::abstract_node<position_interpolator_node>,
        public openvrml::child_node {

        friend class openvrml_node_vrml97::position_interpolator_metatype;

        class set_fraction_listener : public openvrml::node_impl_util::event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(position_interpolator_node & node);
            virtual ~set_fraction_listener() OPENVRML_NOTHROW;

        private:
            virtual void do_process_event(const openvrml::sffloat & fraction,
                                          double timestamp)
                OPENVRML_THROW1(std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<openvrml::mffloat> key_;
        exposedfield<openvrml::mfvec3f> key_value_;
        openvrml::sfvec3f value_changed_;
        sfvec3f_emitter value_changed_emitter_;

    public:
        position_interpolator_node(
            const openvrml::node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~position_interpolator_node() OPENVRML_NOTHROW;
    };

    /**
     * @class position_interpolator_node
     *
     * @brief PositionInterpolator node instances.
     */

    /**
     * @var class position_interpolator_node::position_interpolator_metatype
     *
     * @brief Class object for PositionInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class position_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  position_interpolator_node.
     */
    position_interpolator_node::set_fraction_listener::
    set_fraction_listener(position_interpolator_node & node):
        openvrml::node_event_listener(node),
        openvrml::node_impl_util::event_listener_base<position_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    position_interpolator_node::set_fraction_listener::
    ~set_fraction_listener() OPENVRML_NOTHROW
    {}

    /**
     * @brief Process event.
     *
     * @param fraction  fraction.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    position_interpolator_node::set_fraction_listener::
    do_process_event(const openvrml::sffloat & fraction, const double timestamp)
        OPENVRML_THROW1(std::bad_alloc)
    {
        try {
            using std::vector;
            using openvrml::vec3f;

            position_interpolator_node & node =
                dynamic_cast<position_interpolator_node &>(this->node());

            const vector<float> & key = node.key_.mffloat::value();
            const vector<vec3f> & key_value = node.key_value_.mfvec3f::value();

            vector<float>::size_type n = key.size() - 1;
            if (fraction.value() < key[0]) {
                node.value_changed_.value(key_value[0]);
            } else if (fraction.value() > key[n]) {
                node.value_changed_.value(key_value[n]);
            } else {
                // should cache the last index used...
                for (vector<float>::size_type i = 0; i < n; ++i) {
                    if (key[i] <= fraction.value()
                        && fraction.value() <= key[i + 1]) {
                        const vec3f & v1 = key_value[i];
                        const vec3f & v2 = key_value[i + 1];

                        const float f =
                            (fraction.value() - key[i])
                            / (key[i + 1] - key[i]);
                        node.value_changed_.value(v1 + f * (v2 - v1));
                        break;
                    }
                }
            }

            // Send the new value
            node::emit_event(node.value_changed_emitter_, timestamp);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var position_interpolator_node::set_fraction_listener position_interpolator_node::set_fraction_listener_
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<position_interpolator_node>::exposedfield<openvrml::mffloat> position_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<position_interpolator_node>::exposedfield<openvrml::mfvec3f> position_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::sfvec3f position_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter position_interpolator_node::value_changed_emitter_
     *
     * @brief value_changed eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    position_interpolator_node::
    position_interpolator_node(const openvrml::node_type & type,
                               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        openvrml::node_impl_util::abstract_node<position_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_emitter_(*this, this->value_changed_)
    {}

    /**
     * @brief Destroy.
     */
    position_interpolator_node::
    ~position_interpolator_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::position_interpolator_metatype::id =
    "urn:X-openvrml:node:PositionInterpolator";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this @c node_metatype.
 */
openvrml_node_vrml97::position_interpolator_metatype::
position_interpolator_metatype(openvrml::browser & browser):
    node_metatype(position_interpolator_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::position_interpolator_metatype::
~position_interpolator_metatype() OPENVRML_NOTHROW
{}

/**
 * @brief Create a node_type.
 *
 * @param id            the name for the new node_type.
 * @param interfaces    the interfaces for the new node_type.
 *
 * @return a boost::shared_ptr<node_type> to a node_type capable of
 *         creating PositionInterpolator nodes.
 *
 * @exception openvrml::unsupported_interface if @p interfaces includes an interface
 *                                  not supported by
 *                                  position_interpolator_metatype.
 * @exception std::bad_alloc        if memory allocation fails.
 */
const boost::shared_ptr<openvrml::node_type>
openvrml_node_vrml97::position_interpolator_metatype::
do_create_type(const std::string & id,
               const openvrml::node_interface_set & interfaces) const
    OPENVRML_THROW2(openvrml::unsupported_interface, std::bad_alloc)
{
    using namespace openvrml;
    using namespace openvrml::node_impl_util;

    typedef boost::array<node_interface, 5> supported_interfaces_t;
    static const supported_interfaces_t supported_interfaces = {
        node_interface(node_interface::eventin_id,
                       field_value::sffloat_id,
                       "set_fraction"),
        node_interface(node_interface::exposedfield_id,
                       field_value::mffloat_id,
                       "key"),
        node_interface(node_interface::exposedfield_id,
                       field_value::mfvec3f_id,
                       "keyValue"),
        node_interface(node_interface::eventout_id,
                       field_value::sfvec3f_id,
                       "value_changed"),
        node_interface(node_interface::exposedfield_id,
                       field_value::sfnode_id,
                       "metadata")
    };

    typedef node_impl_util::node_type_impl<position_interpolator_node> node_type_t;

    const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
    node_type_t & positionInterpolatorNodeType =
        static_cast<node_type_t &>(*type);
    for (node_interface_set::const_iterator interface_(interfaces.begin());
         interface_ != interfaces.end();
         ++interface_) {
        supported_interfaces_t::const_iterator supported_interface =
            supported_interfaces.begin() - 1;
        if (*interface_ == *++supported_interface) {
            positionInterpolatorNodeType.add_eventin(
                supported_interface->field_type,
                supported_interface->id,
                node_type_t::event_listener_ptr_ptr(
                    new node_type_t::event_listener_ptr<
                    position_interpolator_node::set_fraction_listener>(
                        &position_interpolator_node::set_fraction_listener_)));
        } else if (*interface_ == *++supported_interface) {
            positionInterpolatorNodeType.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                node_type_t::event_listener_ptr_ptr(
                    new node_type_t::event_listener_ptr<
                    abstract_node<position_interpolator_node>::
                    exposedfield<mffloat> >(
                        &position_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<position_interpolator_node>::
                        exposedfield<mffloat> >(
                            &position_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<position_interpolator_node>::
                        exposedfield<mffloat> >(
                            &position_interpolator_node::key_)));
        } else if (*interface_ == *++supported_interface) {
            positionInterpolatorNodeType.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                node_type_t::event_listener_ptr_ptr(
                    new node_type_t::event_listener_ptr<
                    abstract_node<position_interpolator_node>::
                    exposedfield<mfvec3f> >(
                        &position_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<position_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &position_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<position_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &position_interpolator_node::key_value_)));
        } else if (*interface_ == *++supported_interface) {
            positionInterpolatorNodeType.add_eventout(
                supported_interface->field_type,
                supported_interface->id,
                node_type_t::event_emitter_ptr_ptr(
                    new node_type_t::event_emitter_ptr<
                    abstract_node<position_interpolator_node>::
                    sfvec3f_emitter>(
                        &position_interpolator_node::value_changed_emitter_)));
        } else if (*interface_ == *++supported_interface) {
            positionInterpolatorNodeType.add_exposedfield(
                supported_interface->field_type,
                supported_interface->id,
                node_type_t::event_listener_ptr_ptr(
                    new node_type_t::event_listener_ptr<
                    abstract_node<position_interpolator_node>::exposedfield<sfnode> >(
                        &position_interpolator_node::metadata)),
                node_type_t::field_ptr_ptr(
                    new node_type_t::field_ptr<
                    abstract_node<position_interpolator_node>::exposedfield<sfnode> >(
                        &position_interpolator_node::metadata)),
                node_type_t::event_emitter_ptr_ptr(
                    new node_type_t::event_emitter_ptr<
                    abstract_node<position_interpolator_node>::exposedfield<sfnode> >(
                        &position_interpolator_node::metadata)));
        } else {
            throw unsupported_interface(*interface_);
        }
    }
    return type;
}
