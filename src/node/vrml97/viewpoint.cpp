// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009  Braden McDaniel
// Copyright 2002  S. K. Bose
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

# include "viewpoint.h"
# include <openvrml/browser.h>
# include <openvrml/scene.h>
# include <private.h>
# include <boost/array.hpp>

/**
 * @var openvrml_node_vrml97::viewpoint_node * openvrml_node_vrml97::viewpoint_metatype::first
 *
 * @brief The first Viewpoint node in the initial scene graph.
 */

/**
 * @var openvrml::node_impl_util::bound_node_stack<openvrml_node_vrml97::viewpoint_node> openvrml_node_vrml97::viewpoint_metatype::bound_nodes
 *
 * @brief The stack of bound Viewpoint nodes.
 */

/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::viewpoint_metatype::id = "urn:X-openvrml:node:Viewpoint";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this @c node_metatype.
 */
openvrml_node_vrml97::viewpoint_metatype::
viewpoint_metatype(openvrml::browser & browser):
    node_metatype(viewpoint_metatype::id, browser),
    first(0)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::viewpoint_metatype::~viewpoint_metatype() OPENVRML_NOTHROW
{}

/**
 * @brief Set the first Viewpoint node in the world.
 *
 * The first Viewpoint node in the world is used as the initial viewpoint.
 * This function is used by @c viewpoint_node::do_initialize.
 *
 * @param viewpoint    a Viewpoint node.
 */
void
openvrml_node_vrml97::viewpoint_metatype::set_first(viewpoint_node & viewpoint)
    OPENVRML_NOTHROW
{
    assert(!this->has_first());
    this->first = &viewpoint;
}

/**
 * @brief Reset the pointer to the first Viewpoint node in the world to
 *        null.
 *
 * This function is called by @c viewpoint_node::do_shutdown.
 */
void openvrml_node_vrml97::viewpoint_metatype::reset_first() OPENVRML_NOTHROW
{
    this->first = 0;
}

/**
 * @brief Check to see if the first node has been set.
 *
 * This method is used by @c viewpoint_node::do_initialize.
 *
 * @return @c true if the first node has already been set; @c false
 *         otherwise.
 */
bool openvrml_node_vrml97::viewpoint_metatype::has_first() const OPENVRML_NOTHROW
{
    return this->first;
}

/**
 * @brief Check to see if a node is registered as the &ldquo;first&rdquo; node.
 *
 * @param viewpoint a @c viewpoint_node.
 *
 * @return @c true if @p viewpoint is the fist node; @c false otherwise.
 */
bool
openvrml_node_vrml97::viewpoint_metatype::is_first(viewpoint_node & viewpoint)
    OPENVRML_NOTHROW
{
    return &viewpoint == this->first;
}

/**
 * @brief Push a Viewpoint on the top of the bound node stack.
 *
 * @param viewpoint    the node to bind.
 * @param timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml_node_vrml97::viewpoint_metatype::bind(viewpoint_node & viewpoint,
                                                    const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    this->bound_nodes.bind(viewpoint, timestamp);
    this->browser().active_viewpoint(viewpoint);
}

/**
 * @brief Remove a Viewpoint from the bound node stack.
 *
 * @param viewpoint    the node to unbind.
 * @param timestamp    the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml_node_vrml97::viewpoint_metatype::unbind(viewpoint_node & viewpoint,
                                                 const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    this->bound_nodes.unbind(viewpoint, timestamp);
    if (this->bound_nodes.empty()) {
        this->browser().reset_default_viewpoint();
    } else {
        this->browser().active_viewpoint(*this->bound_nodes.top());
    }
}

/**
 * @brief @c node_metatype%-specific initialization.
 *
 * @param initial_viewpoint the @c viewpoint_node that should be bound
 *                          initially.
 * @param timestamp         the current time.
 */
void
openvrml_node_vrml97::viewpoint_metatype::
do_initialize(openvrml::viewpoint_node * initial_viewpoint,
              const double timestamp)
    OPENVRML_NOTHROW
{
    using namespace openvrml;
    if (!initial_viewpoint) { initial_viewpoint = this->first; }
    if (initial_viewpoint) {
        try {
            event_listener & listener =
                this->first->event_listener("set_bind");
            dynamic_cast<sfbool_listener &>(listener)
                .process_event(sfbool(true), timestamp);
        } catch (unsupported_interface & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }
}

//
// description is a field in VRML97 and an exposedField in X3D.
//
# define VIEWPOINT_INTERFACE_SEQ                                        \
    ((eventin,      sfbool,     "set_bind",         set_bind_listener_)) \
    ((exposedfield, sffloat,    "fieldOfView",      field_of_view_))    \
    ((exposedfield, sfbool,     "jump",             jump_))             \
    ((exposedfield, sfrotation, "orientation",      orientation_))      \
    ((exposedfield, sfvec3f,    "position",         position_))         \
    ((field,        sfstring,   "description",      description_))      \
    ((exposedfield, sfstring,   "description",      description_))      \
    ((eventout,     sftime,     "bindTime",         bind_time_emitter_)) \
    ((eventout,     sfbool,     "isBound",          is_bound_emitter_)) \
    ((exposedfield, sfnode,     "metadata",         metadata))          \
    ((exposedfield, sfvec3f,    "centerOfRotation", center_of_rotation_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_vrml97,
                                              viewpoint_metatype,
                                              viewpoint_node,
                                              VIEWPOINT_INTERFACE_SEQ)

/**
 * @class openvrml_node_vrml97::viewpoint_node
 *
 * @brief Viewpoint node instance.
 */

/**
 * @var class openvrml_node_vrml97::viewpoint_node::viewpoint_metatype
 *
 * @brief Class object for Viewpoint nodes.
 */

/**
 * @internal
 *
 * @class openvrml_node_vrml97::viewpoint_node::set_bind_listener
 *
 * @brief set_bind eventIn listener.
 */

/**
 * @brief Construct.
 *
 * @param node viewpoint_node.
 */
openvrml_node_vrml97::viewpoint_node::set_bind_listener::
set_bind_listener(viewpoint_node & node):
    openvrml::node_event_listener(node),
    openvrml::node_impl_util::event_listener_base<viewpoint_node>(node),
    sfbool_listener(node)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::viewpoint_node::set_bind_listener::~set_bind_listener()
    OPENVRML_NOTHROW
{}

/**
 * @brief Process an event.
 *
 * @param value     event value.
 * @param timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml_node_vrml97::viewpoint_node::set_bind_listener::
do_process_event(const openvrml::sfbool & value, const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    try {
        viewpoint_node & node =
            dynamic_cast<viewpoint_node &>(this->node());
        viewpoint_metatype & node_metatype =
            const_cast<viewpoint_metatype &>(
                static_cast<const viewpoint_metatype &>(
                    node.type().metatype()));
        if (value.value()) {
            node_metatype.bind(node, timestamp);
        } else {
            node_metatype.unbind(node, timestamp);
        }
    } catch (std::bad_cast & ex) {
        OPENVRML_PRINT_EXCEPTION_(ex);
    }
}

/**
 * @internal
 *
 * @class viewpoint_node::orientation_exposedfield
 *
 * @brief orientation exposedField implementation.
 */

/**
 * @brief Construct.
 *
 * @param node viewpoint_node.
 */
openvrml_node_vrml97::viewpoint_node::orientation_exposedfield::
orientation_exposedfield(viewpoint_node & node):
    openvrml::node_event_listener(node),
    openvrml::event_emitter(static_cast<const openvrml::field_value &>(*this)),
    sfrotation_listener(node),
    exposedfield<openvrml::sfrotation>(node)
{}

/**
 * @brief Construct a copy.
 *
 * @param obj   instance to copy.
 */
openvrml_node_vrml97::viewpoint_node::orientation_exposedfield::
orientation_exposedfield(const orientation_exposedfield & obj) OPENVRML_NOTHROW:
openvrml::event_listener(),
    openvrml::node_event_listener(obj.openvrml::node_event_listener::node()),
    openvrml::event_emitter(static_cast<const openvrml::field_value &>(*this)),
    sfrotation_listener(obj.openvrml::node_event_listener::node()),
    exposedfield<openvrml::sfrotation>(obj)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::viewpoint_node::orientation_exposedfield::
~orientation_exposedfield() OPENVRML_NOTHROW
{}

/**
 * @brief Polymorphically construct a copy.
 *
 * @return a copy of the instance.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
std::auto_ptr<openvrml::field_value>
openvrml_node_vrml97::viewpoint_node::orientation_exposedfield::
do_clone() const OPENVRML_THROW1(std::bad_alloc)
{
    return std::auto_ptr<openvrml::field_value>(
        new orientation_exposedfield(*this));
}

/**
 * @brief Process an event.
 *
 * @param orientation   orientation.
 * @param timestamp     the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml_node_vrml97::viewpoint_node::orientation_exposedfield::
event_side_effect(const openvrml::sfrotation &, double)
    OPENVRML_THROW1(std::bad_alloc)
{
    try {
        viewpoint_node & node =
            dynamic_cast<viewpoint_node &>(this->node_event_listener::node());
        node.final_transformation_dirty = true;
    } catch (std::bad_cast & ex) {
        OPENVRML_PRINT_EXCEPTION_(ex);
    }
}

/**
 * @internal
 *
 * @class viewpoint_node::position_exposedfield
 *
 * @brief position exposedField implementation.
 */

/**
 * @brief Construct.
 *
 * @param node viewpoint_node.
 */
openvrml_node_vrml97::viewpoint_node::position_exposedfield::
position_exposedfield(viewpoint_node & node):
    openvrml::node_event_listener(node),
    openvrml::event_emitter(static_cast<const openvrml::field_value &>(*this)),
    sfvec3f_listener(node),
    exposedfield<openvrml::sfvec3f>(
        node,
        openvrml::make_vec3f(0.0f, 0.0f, 10.0f))
{}

/**
 * @brief Construct a copy.
 *
 * @param obj   instance to copy.
 */
openvrml_node_vrml97::viewpoint_node::position_exposedfield::
position_exposedfield(const position_exposedfield & obj) OPENVRML_NOTHROW:
openvrml::event_listener(),
    openvrml::node_event_listener(obj.openvrml::node_event_listener::node()),
    openvrml::event_emitter(static_cast<const openvrml::field_value &>(*this)),
    sfvec3f_listener(obj.openvrml::node_event_listener::node()),
    exposedfield<openvrml::sfvec3f>(obj)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::viewpoint_node::position_exposedfield::
~position_exposedfield() OPENVRML_NOTHROW
{}

/**
 * @brief Polymorphically construct a copy.
 *
 * @return a copy of the instance.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
std::auto_ptr<openvrml::field_value>
openvrml_node_vrml97::viewpoint_node::position_exposedfield::do_clone() const
    OPENVRML_THROW1(std::bad_alloc)
{
    return std::auto_ptr<openvrml::field_value>(
        new position_exposedfield(*this));
}

/**
 * @brief Process an event.
 *
 * @param position  position.
 * @param timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml_node_vrml97::viewpoint_node::position_exposedfield::
event_side_effect(const openvrml::sfvec3f &, double)
    OPENVRML_THROW1(std::bad_alloc)
{
    try {
        viewpoint_node & node =
            dynamic_cast<viewpoint_node &>(
                this->node_event_listener::node());
        node.final_transformation_dirty = true;
    } catch (std::bad_cast & ex) {
        OPENVRML_PRINT_EXCEPTION_(ex);
    }
}

/**
 * @var openvrml_node_vrml97::viewpoint_node::set_bind_listener openvrml_node_vrml97::viewpoint_node::set_bind_listener_
 *
 * @brief set_bind eventIn handler.
 */

/**
 * @var openvrml::node_impl_util::abstract_node<openvrml_node_vrml97::viewpoint_node>::exposedfield<openvrml::sffloat> openvrml_node_vrml97::viewpoint_node::field_of_view_
 *
 * @brief fieldOfView exposedField.
 */

/**
 * @var openvrml::node_impl_util::abstract_node<openvrml_node_vrml97::viewpoint_node>::exposedfield<openvrml::sfbool> openvrml_node_vrml97::viewpoint_node::jump_
 *
 * @brief jump exposedField.
 */

/**
 * @var viewpoint_node::orientation_exposedfield openvrml_node_vrml97::viewpoint_node::orientation_
 *
 * @brief orientation exposedField.
 */

/**
 * @var viewpoint_node::position_exposedfield openvrml_node_vrml97::viewpoint_node::position_
 *
 * @brief position exposedField.
 */

/**
 * @var openvrml::sfstring openvrml_node_vrml97::viewpoint_node::description_
 *
 * @brief description field.
 */

/**
 * @var openvrml::sfbool openvrml_node_vrml97::viewpoint_node::is_bound_
 *
 * @brief isBound eventOut value.
 */

/**
 * @var openvrml::sfbool_emitter openvrml_node_vrml97::viewpoint_node::is_bound_emitter_
 *
 * @brief isBound eventOut emitter.
 */

/**
 * @var openvrml::sftime openvrml_node_vrml97::viewpoint_node::bind_time_
 *
 * @brief bindTime eventOut value.
 */

/**
 * @var openvrml::sftime_emitter openvrml_node_vrml97::viewpoint_node::bind_time_emitter_
 *
 * @brief bindTime eventOut emitter.
 */

/**
 * @var openvrml::mat4f openvrml_node_vrml97::viewpoint_node::parent_transform
 *
 * @brief The accumulated transformation applied by any parent nodes.
 */

/**
 * @var openvrml::mat4f openvrml_node_vrml97::viewpoint_node::final_transformation
 *
 * @brief The product of @a parent_transform and any transformation applied
 *        by the Viewpoint node.
 */

/**
 * @var bool openvrml_node_vrml97::viewpoint_node::final_transformation_dirty
 *
 * @brief Flag that indicates if @a final_transformation needs to be
 *        updated.
 */

/**
 * @var openvrml::mat4f openvrml_node_vrml97::viewpoint_node::user_view_transform_
 *
 * @brief The transformation applied to the user view.
 *
 * Generally the result of any user navigation.
 */

const float DEFAULT_FIELD_OF_VIEW = 0.785398f;

/**
 * @brief Construct.
 *
 * @param type      the @c node_type associated with the instance.
 * @param scope     the scope that the new node will belong to.
 */
openvrml_node_vrml97::viewpoint_node::
viewpoint_node(const openvrml::node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope):
    node(type, scope),
    openvrml::node_impl_util::abstract_node<viewpoint_node>(type, scope),
    openvrml::viewpoint_node(type, scope),
    set_bind_listener_(*this),
    field_of_view_(*this, DEFAULT_FIELD_OF_VIEW),
    jump_(*this, true),
    orientation_(*this),
    position_(*this),
    description_(*this),
    center_of_rotation_(*this),
    is_bound_emitter_(*this, this->is_bound_),
    bind_time_emitter_(*this, this->bind_time_),
    parent_transform(openvrml::make_mat4f()),
    final_transformation(openvrml::make_mat4f()),
    final_transformation_dirty(true),
    user_view_transform_(openvrml::make_mat4f())
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::viewpoint_node::~viewpoint_node() OPENVRML_NOTHROW
{}

/**
 * @brief Set the bind state.
 *
 * This function is called by
 * <code>bound_node_stack<BindableNode>::bind</code>.  It sets the
 * "bind" state and fires an event; it does not actually put the
 * node onto the bound node stack.
 *
 * @param[in] val       the bind state.
 * @param[in] timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml_node_vrml97::viewpoint_node::bind(const bool val,
                                                const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    this->is_bound_.value(val);
    node::emit_event(this->is_bound_emitter_, timestamp);
}

/**
 * @brief Get the transformation of the @c viewpoint_node in the global
 *        coordinate system.
 *
 * @return the transformation of the @c viewpoint_node in the global
 *         coordinate system.
 */
const openvrml::mat4f &
openvrml_node_vrml97::viewpoint_node::do_transformation() const OPENVRML_NOTHROW
{
    this->update_final_transformation();
    return this->final_transformation;
}

/**
 * @brief Get the transformation of the user view relative to the
 *        @c viewpoint_node.
 *
 * @return the transformation of the user view relative to the
 *         @c viewpoint_node.
 */
const openvrml::mat4f &
openvrml_node_vrml97::viewpoint_node::do_user_view_transform() const
    OPENVRML_NOTHROW
{
    return this->user_view_transform_;
}

/**
 * @brief Set the transformation of the user view relative to the
 *        @c viewpoint_node.
 *
 * @param transform the new transformation.
 */
void
openvrml_node_vrml97::viewpoint_node::
do_user_view_transform(const openvrml::mat4f & transform) OPENVRML_NOTHROW
{
    this->user_view_transform_ = transform;
}

/**
 * @brief description accessor.
 *
 * @return the description.
 */
const std::string & openvrml_node_vrml97::viewpoint_node::do_description() const
    OPENVRML_NOTHROW
{
    return this->description_.sfstring::value();
}

/**
 * @brief Get the field of view.
 *
 * @return the field of view in radians.
 */
float openvrml_node_vrml97::viewpoint_node::do_field_of_view() const
    OPENVRML_NOTHROW
{
    return this->field_of_view_.sffloat::value();
}

/**
 * @brief orientation accessor.
 *
 * @return the orientation.
 */
const openvrml::sfrotation &
openvrml_node_vrml97::viewpoint_node::orientation() const
{
    return this->orientation_;
}

/**
 * @brief position accessor.
 *
 * @return the position.
 */
const openvrml::sfvec3f &
openvrml_node_vrml97::viewpoint_node::position() const
{
    return this->position_;
}

/**
 * @brief Initialize.
 *
 * @param timestamp the current time.
 */
void
openvrml_node_vrml97::viewpoint_node::do_initialize(double)
    OPENVRML_NOTHROW
{
    using boost::polymorphic_downcast;
    assert(this->scene());
    this->scene()->browser().add_viewpoint(*this);
    viewpoint_metatype & nodeClass =
        const_cast<viewpoint_metatype &>(
            *polymorphic_downcast<const viewpoint_metatype *>(
                &this->type().metatype()));
    if (!nodeClass.has_first()) { nodeClass.set_first(*this); }
}

struct OPENVRML_LOCAL accumulate_transform_ :
    std::unary_function<openvrml::node *, void> {

    explicit accumulate_transform_(openvrml::mat4f & transform) OPENVRML_NOTHROW:
        transform(&transform)
    {}

    void operator()(openvrml::node * node) const OPENVRML_NOTHROW
    {
        using openvrml::node_cast;
        using openvrml::transform_node;
        assert(node);
        transform_node * const t = node_cast<transform_node *>(node);
        if (t) { *this->transform = t->transform() * *this->transform; }
    }

private:
    openvrml::mat4f * transform;
};

/**
 * @brief Relocate.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml_node_vrml97::viewpoint_node::do_relocate()
    OPENVRML_THROW1(std::bad_alloc)
{
    assert(this->scene());
    const openvrml::node_path path =
        this->scene()->browser().find_node(*this);
    assert(!path.empty());
    this->parent_transform = openvrml::make_mat4f();
    std::for_each(path.begin(), path.end(),
                  accumulate_transform_(this->parent_transform));
    this->final_transformation_dirty = true;
}

/**
 * @brief Shut down.
 *
 * @param timestamp the current time.
 */
void openvrml_node_vrml97::viewpoint_node::do_shutdown(const double timestamp)
    OPENVRML_NOTHROW
{
    viewpoint_metatype & node_metatype =
        const_cast<viewpoint_metatype &>(
            static_cast<const viewpoint_metatype &>(
                this->type().metatype()));
    node_metatype.unbind(*this, timestamp);
    assert(this->scene());
    this->scene()->browser().remove_viewpoint(*this);

    if (node_metatype.is_first(*this)) { node_metatype.reset_first(); }
}

/**
 * @brief Update @a final_transformation.
 *
 * If @a final_transformation_dirty is @c true, update
 * @a final_transformation and sets @a final_transformation_dirty to
 * @c false; otherwise, do nothing.
 */
void openvrml_node_vrml97::viewpoint_node::update_final_transformation() const
    OPENVRML_NOTHROW
{
    using namespace openvrml;

    if (this->final_transformation_dirty) {
        static const vec3f scale = make_vec3f(1.0, 1.0, 1.0);
        static const rotation scaleOrientation = make_rotation();
        const mat4f & t =
            make_transformation_mat4f(
                this->position_.sfvec3f::value(),
                this->orientation_.sfrotation::value(),
                scale,
                scaleOrientation,
                this->center_of_rotation_.sfvec3f::value()
            );
        this->final_transformation = t * this->parent_transform;
        this->final_transformation_dirty = false;
    }
}
