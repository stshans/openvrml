// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009  Braden McDaniel
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

# include "appearance.h"
# include <openvrml/browser.h>
# include <openvrml/node_impl_util.h>
# include <openvrml/viewer.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

namespace {

    class OPENVRML_LOCAL appearance_node :
        public openvrml::node_impl_util::abstract_node<appearance_node>,
        public openvrml::appearance_node {

        friend class openvrml_node_vrml97::appearance_metatype;

        exposedfield<openvrml::sfnode> material_;
        exposedfield<openvrml::sfnode> texture_;
        exposedfield<openvrml::sfnode> texture_transform_;
        exposedfield<openvrml::sfnode> fill_properties_;
        exposedfield<openvrml::sfnode> line_properties_;

    public:
        appearance_node(const openvrml::node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~appearance_node() OPENVRML_NOTHROW;

    private:
        virtual bool do_modified() const
            OPENVRML_THROW1(boost::thread_resource_error);

        //
        // appearance_node implementation
        //
        virtual const boost::intrusive_ptr<node> & do_material() const
            OPENVRML_NOTHROW;
        virtual const boost::intrusive_ptr<node> & do_texture() const
            OPENVRML_NOTHROW;
        virtual const boost::intrusive_ptr<node> & do_texture_transform() const
            OPENVRML_NOTHROW;
        virtual void do_render_appearance(openvrml::viewer & v,
                                          openvrml::rendering_context context);
    };

    /**
     * @class appearance_node
     *
     * @brief Appearance node instances.
     */

    /**
     * @var class appearance_node::appearance_metatype
     *
     * @brief Class object for Appearance nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<appearance_node>::exposedfield<openvrml::sfnode> appearance_node::material_
     *
     * @brief material exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<appearance_node>::exposedfield<openvrml::sfnode> appearance_node::texture_
     *
     * @brief texture exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<appearance_node>::exposedfield<openvrml::sfnode> appearance_node::texture_transform_
     *
     * @brief textureTransform exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    appearance_node::
    appearance_node(const openvrml::node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        openvrml::node_impl_util::abstract_node<appearance_node>(type, scope),
        openvrml::appearance_node(type, scope),
        material_(*this),
        texture_(*this),
        texture_transform_(*this),
        fill_properties_(*this),
        line_properties_(*this)
    {}

    /**
     * @brief Destroy.
     */
    appearance_node::~appearance_node() OPENVRML_NOTHROW
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *         @c false otherwise.
     */
    bool appearance_node::do_modified() const
        OPENVRML_THROW1(boost::thread_resource_error)
    {
        return (this->material_.value() && this->material_.value()->modified())
            || (this->texture_.value() && this->texture_.value()->modified())
            || (this->texture_transform_.value()
                && this->texture_transform_.value()->modified());
    }

    /**
     * @brief Get the material node.
     *
     * @returns an sfnode object containing the Material node associated with
     *          this Appearance.
     */
    const boost::intrusive_ptr<openvrml::node> &
    appearance_node::do_material() const OPENVRML_NOTHROW
    {
        return this->material_.sfnode::value();
    }

    /**
     * @brief Get the texture node.
     *
     * @return an sfnode object containing the texture node associated with
     *         this Appearance.
     */
    const boost::intrusive_ptr<openvrml::node> &
    appearance_node::do_texture() const OPENVRML_NOTHROW
    {
        return this->texture_.sfnode::value();
    }

    /**
     * @brief Get the texture transform node.
     *
     * @return an sfnode object containing the TextureTransform node
     *         associated with this Appearance.
     */
    const boost::intrusive_ptr<openvrml::node> &
    appearance_node::do_texture_transform() const OPENVRML_NOTHROW
    {
        return this->texture_transform_.sfnode::value();
    }

    OPENVRML_LOCAL void set_unlit_material(openvrml::viewer & v)
    {
        using openvrml::color;
        using openvrml::make_color;
        static const float unlit_ambient_intensity(1);
        static const color unlit_diffuse_color = make_color(1, 1, 1);
        static const color unlit_emissive_color = make_color(1, 1, 1);
        static const float unlit_shininess(0);
        static const color unlit_specular_color = make_color(1, 1, 1);
        static const float unlit_transparency(0);
        v.set_material(unlit_ambient_intensity,
                       unlit_diffuse_color,
                       unlit_emissive_color,
                       unlit_shininess,
                       unlit_specular_color,
                       unlit_transparency);
    }

    /**
     * @brief render_appearance implementation.
     *
     * @param v         viewer.
     * @param context   rendering_context.
     */
    void
    appearance_node::
    do_render_appearance(openvrml::viewer & v, openvrml::rendering_context)
    {
        using namespace openvrml;

        openvrml::material_node * const material =
            node_cast<openvrml::material_node *>(
                this->material_.sfnode::value().get());
        texture_node * const texture =
            node_cast<texture_node *>(this->texture_.sfnode::value().get());

        if (material) {
            float trans = material->transparency();
            color diffuse = material->diffuse_color();
            size_t nTexComponents = texture ? texture->image().comp() : 0;
            if (nTexComponents == 2 || nTexComponents == 4) { trans = 0.0; }
            if (nTexComponents >= 3) { diffuse = make_color(1.0, 1.0, 1.0); }

            v.enable_lighting(true);   // turn lighting on for this object
            v.set_material(material->ambient_intensity(),
                           diffuse,
                           material->emissive_color(),
                           material->shininess(),
                           material->specular_color(),
                           trans);

            material->modified(false);
        } else {
            v.enable_lighting(false);   // turn lighting off for this object
            set_unlit_material(v);
        }

        if (texture) {
            openvrml::texture_transform_node * texture_transform =
                node_cast<openvrml::texture_transform_node *>(
                    this->texture_transform_.sfnode::value().get());
            if (texture_transform) {
                texture_transform->render_texture_transform(v);
            } else {
                static const vec2f center = make_vec2f(0.0, 0.0);
                static const float rotation = 0.0;
                static const vec2f scale = make_vec2f(1.0, 1.0);
                static const vec2f translation = make_vec2f(0.0, 0.0);
                v.set_texture_transform(center, rotation, scale, translation);
            }
            texture->render_texture(v);
        }
    }
}

/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::appearance_metatype::id =
    "urn:X-openvrml:node:Appearance";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this class object.
 */
openvrml_node_vrml97::appearance_metatype::
appearance_metatype(openvrml::browser & browser):
    node_metatype(appearance_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::appearance_metatype::~appearance_metatype()
    OPENVRML_NOTHROW
{}

# define APPEARANCE_INTERFACE_SEQ                                       \
    ((exposedfield, sfnode, "material",         material_))             \
    ((exposedfield, sfnode, "texture",          texture_))              \
    ((exposedfield, sfnode, "textureTransform", texture_transform_))    \
    ((exposedfield, sfnode, "metadata",         metadata))              \
    ((exposedfield, sfnode, "fillProperties",   fill_properties_))      \
    ((exposedfield, sfnode, "lineProperties",   line_properties_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_vrml97,
                                              appearance_metatype,
                                              appearance_node,
                                              APPEARANCE_INTERFACE_SEQ)
