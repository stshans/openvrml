// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 1999  Kumaran Santhanam
// Copyright 2001, 2002, 2003, 2004, 2005  Braden McDaniel
// Copyright 2002  S. K. Bose
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

# ifdef OPENVRML_ENABLE_PNG_TEXTURES
#   include <png.h>
# endif
# ifdef OPENVRML_ENABLE_JPEG_TEXTURES
#   include <jpeglib.h>
# endif
# include <algorithm>
# include <iterator>
# include <limits>
# include <boost/algorithm/string/predicate.hpp>
# include <boost/array.hpp>
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
#   include <ft2build.h>
#   include FT_FREETYPE_H
#   include FT_GLYPH_H
#   include FT_OUTLINE_H
#   include <fontconfig/fontconfig.h>
extern "C" {
#   include <fontconfig/fcfreetype.h>
}
# endif
# include <private.h>
# include "vrml97node.h"
# include "browser.h"
# include "node_impl_util.h"

template void std::vector<boost::intrusive_ptr<openvrml::node> >::pop_back();

namespace {

    using namespace openvrml;
    using namespace openvrml::node_impl_util;

    /**
     * @brief Class object for Anchor nodes.
     */
    class OPENVRML_LOCAL anchor_class : public node_class {
    public:
        explicit anchor_class(openvrml::browser & browser);
        virtual ~anchor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };

    /**
     * @brief Class object for Appearance nodes.
     */
    class OPENVRML_LOCAL appearance_class : public node_class {
    public:
        explicit appearance_class(openvrml::browser & browser);
        virtual ~appearance_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for AudioClip nodes.
     */
    class OPENVRML_LOCAL audio_clip_class : public node_class {
    public:
        explicit audio_clip_class(openvrml::browser & browser);
        virtual ~audio_clip_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    class background_node;

    /**
     * @brief Class object for Background nodes.
     */
    class OPENVRML_LOCAL background_class : public node_class {
        typedef std::vector<background_node *> bound_nodes_t;

        background_node * first;
        bound_nodes_t bound_nodes;

    public:
        explicit background_class(openvrml::browser & browser);
        virtual ~background_class() throw ();

        void set_first(background_node & background) throw ();
        void reset_first() throw ();
        bool has_first() const throw ();
        bool is_first(background_node & background) throw ();
        void bind(background_node & background, double timestamp)
            throw (std::bad_alloc);
        void unbind(background_node & background, double timestamp)
            throw ();

    private:
        virtual void
        do_initialize(openvrml::viewpoint_node * initial_viewpoint,
                      double timestamp) throw ();
        virtual void do_render(viewer & v) const throw ();
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };

    /**
     * @typedef background_class::bound_nodes_t
     *
     * @brief A bound Background node stack.
     */

    /**
     * @var background_node * background_class::first
     *
     * @brief The first Background node in the initial scene graph.
     */

    /**
     * @var background_class::bound_nodes_t background_class::bound_nodes
     *
     * @brief The bound Background node stack.
     */

    /**
     * @brief Class object for Billboard nodes.
     */
    class OPENVRML_LOCAL billboard_class : public node_class {
    public:
        explicit billboard_class(openvrml::browser & browser);
        virtual ~billboard_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Box nodes.
     */
    class OPENVRML_LOCAL box_class : public node_class {
    public:
        explicit box_class(openvrml::browser & browser);
        virtual ~box_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Collision nodes.
     */
    class OPENVRML_LOCAL collision_class : public node_class {
    public:
        explicit collision_class(openvrml::browser & browser);
        virtual ~collision_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Color nodes.
     */
    class OPENVRML_LOCAL color_class : public node_class {
    public:
        explicit color_class(openvrml::browser & browser);
        virtual ~color_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for ColorInterpolator nodes.
     */
    class OPENVRML_LOCAL color_interpolator_class : public node_class {
    public:
        explicit color_interpolator_class(openvrml::browser & browser);
        virtual ~color_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Cone nodes.
     */
    class OPENVRML_LOCAL cone_class : public node_class {
    public:
        explicit cone_class(openvrml::browser & browser);
        virtual ~cone_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Coordinate nodes.
     */
    class OPENVRML_LOCAL coordinate_class : public node_class {
    public:
        explicit coordinate_class(openvrml::browser & browser);
        virtual ~coordinate_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for CoordinateInterpolator nodes.
     */
    class OPENVRML_LOCAL coordinate_interpolator_class : public node_class {
    public:
        explicit coordinate_interpolator_class(openvrml::browser & browser);
        virtual ~coordinate_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Cylinder nodes.
     */
    class OPENVRML_LOCAL cylinder_class : public node_class {
    public:
        explicit cylinder_class(openvrml::browser & browser);
        virtual ~cylinder_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for CylinderSensor nodes.
     */
    class OPENVRML_LOCAL cylinder_sensor_class : public node_class {
    public:
        explicit cylinder_sensor_class(openvrml::browser & browser);
        virtual ~cylinder_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for DirectionalLight nodes.
     */
    class OPENVRML_LOCAL directional_light_class : public node_class {
    public:
        explicit directional_light_class(openvrml::browser & browser);
        virtual ~directional_light_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for ElevationGrid nodes.
     */
    class OPENVRML_LOCAL elevation_grid_class : public node_class {
    public:
        explicit elevation_grid_class(openvrml::browser & browser);
        virtual ~elevation_grid_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Extrusion nodes.
     */
    class OPENVRML_LOCAL extrusion_class : public node_class {
    public:
        explicit extrusion_class(openvrml::browser & browser);
        virtual ~extrusion_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    class fog_node;

    /**
     * @brief Class object for Fog nodes.
     */
    class OPENVRML_LOCAL fog_class : public node_class {
        typedef std::vector<fog_node *> bound_nodes_t;

        fog_node * first;
        bound_nodes_t bound_nodes;

    public:
        explicit fog_class(openvrml::browser & browser);
        virtual ~fog_class() throw ();

        void set_first(fog_node & fog) throw ();
        void reset_first() throw ();
        bool has_first() const throw ();
        bool is_first(fog_node & fog) throw ();
        void bind(fog_node & fog, double timestamp) throw (std::bad_alloc);
        void unbind(fog_node & fog, double timestamp) throw ();

    private:
        virtual void
        do_initialize(openvrml::viewpoint_node * initialViewpoint,
                      double timestamp) throw ();
        virtual void do_render(viewer & v) const throw ();
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };

    /**
     * @typedef fog_class::bound_nodes_t
     *
     * @brief A bound Fog node stack.
     */

    /**
     * @var fog_node * fog_class::first
     *
     * @brief The first Fog node in the initial scene graph.
     */

    /**
     * @var fog_class::bound_nodes_t fog_class::bound_nodes
     *
     * @brief The bound Fog node stack.
     */


    /**
     * @brief Class object for FontStyle nodes.
     */
    class OPENVRML_LOCAL font_style_class : public node_class {
    public:
        explicit font_style_class(openvrml::browser & browser);
        virtual ~font_style_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Group nodes.
     */
    class OPENVRML_LOCAL group_class : public node_class {
    public:
        explicit group_class(openvrml::browser & browser);
        virtual ~group_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for ImageTexture nodes.
     */
    class OPENVRML_LOCAL image_texture_class : public node_class {
    public:
        explicit image_texture_class(openvrml::browser & browser);
        virtual ~image_texture_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for IndexedFaceSet nodes.
     */
    class OPENVRML_LOCAL indexed_face_set_class : public node_class {
    public:
        explicit indexed_face_set_class(openvrml::browser & browser);
        virtual ~indexed_face_set_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for IndexedLineSet nodes.
     */
    class OPENVRML_LOCAL indexed_line_set_class : public node_class {
    public:
        explicit indexed_line_set_class(openvrml::browser & browser);
        virtual ~indexed_line_set_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Inline nodes.
     */
    class OPENVRML_LOCAL inline_class : public node_class {
    public:
        explicit inline_class(openvrml::browser & browser);
        virtual ~inline_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for LOD nodes.
     */
    class OPENVRML_LOCAL lod_class : public node_class {
    public:
        explicit lod_class(openvrml::browser & browser);
        virtual ~lod_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Material nodes.
     */
    class OPENVRML_LOCAL material_class : public node_class {
    public:
        explicit material_class(openvrml::browser & browser);
        virtual ~material_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for MovieTexture nodes.
     */
    class OPENVRML_LOCAL movie_texture_class : public node_class {
    public:
        explicit movie_texture_class(openvrml::browser & browser);
        virtual ~movie_texture_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    class navigation_info_node;

    /**
     * @brief Class object for NavigationInfo nodes.
     */
    class OPENVRML_LOCAL navigation_info_class : public node_class {
        typedef std::vector<navigation_info_node *> bound_nodes_t;

        navigation_info_node * first;
        bound_nodes_t bound_nodes;

    public:
        explicit navigation_info_class(openvrml::browser & browser);
        virtual ~navigation_info_class() throw ();

        void set_first(navigation_info_node & nav_info) throw ();
        void reset_first() throw ();
        bool has_first() const throw ();
        bool is_first(navigation_info_node & nav_info) throw ();
        void bind(navigation_info_node & nav_info, double timestamp)
            throw (std::bad_alloc);
        void unbind(navigation_info_node & nav_info, double timestamp)
            throw ();

    private:
        virtual void
        do_initialize(openvrml::viewpoint_node * initial_viewpoint,
                      double timestamp) throw ();
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Normal nodes.
     */
    class OPENVRML_LOCAL normal_class : public node_class {
    public:
        explicit normal_class(openvrml::browser & browser);
        virtual ~normal_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for NormalInterpolator nodes.
     */
    class OPENVRML_LOCAL normal_interpolator_class : public node_class {
    public:
        explicit normal_interpolator_class(openvrml::browser & browser);
        virtual ~normal_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for OrientationInterpolator nodes.
     */
    class OPENVRML_LOCAL orientation_interpolator_class : public node_class {
    public:
        explicit orientation_interpolator_class(
            openvrml::browser & browser);
        virtual ~orientation_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for PixelTexture nodes.
     */
    class OPENVRML_LOCAL pixel_texture_class : public node_class {
    public:
        explicit pixel_texture_class(openvrml::browser & browser);
        virtual ~pixel_texture_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for PlaneSensor nodes.
     */
    class OPENVRML_LOCAL plane_sensor_class : public node_class {
    public:
        explicit plane_sensor_class(openvrml::browser & browser);
        virtual ~plane_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for PointLight nodes.
     */
    class OPENVRML_LOCAL point_light_class : public node_class {
    public:
        explicit point_light_class(openvrml::browser & browser);
        virtual ~point_light_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for PointSet nodes.
     */
    class OPENVRML_LOCAL point_set_class : public node_class {
    public:
        explicit point_set_class(openvrml::browser & browser);
        virtual ~point_set_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for PositionInterpolator nodes.
     */
    class OPENVRML_LOCAL position_interpolator_class : public node_class {
    public:
        explicit position_interpolator_class(openvrml::browser & browser);
        virtual ~position_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for ProximitySensor nodes.
     */
    class OPENVRML_LOCAL proximity_sensor_class : public node_class {
    public:
        explicit proximity_sensor_class(openvrml::browser & browser);
        virtual ~proximity_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for ScalarInterpolator nodes.
     */
    class OPENVRML_LOCAL scalar_interpolator_class : public node_class {
    public:
        explicit scalar_interpolator_class(openvrml::browser & browser);
        virtual ~scalar_interpolator_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Shape nodes.
     */
    class OPENVRML_LOCAL shape_class : public node_class {
    public:
        explicit shape_class(openvrml::browser & browser);
        virtual ~shape_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Sound nodes.
     */
    class OPENVRML_LOCAL sound_class : public node_class {
    public:
        explicit sound_class(openvrml::browser & browser);
        virtual ~sound_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Sphere nodes.
     */
    class OPENVRML_LOCAL sphere_class : public node_class {
    public:
        explicit sphere_class(openvrml::browser & browser);
        virtual ~sphere_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for SphereSensor nodes.
     */
    class OPENVRML_LOCAL sphere_sensor_class : public node_class {
    public:
        explicit sphere_sensor_class(openvrml::browser & browser);
        virtual ~sphere_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for SpotLight nodes.
     */
    class OPENVRML_LOCAL spot_light_class : public node_class {
    public:
        explicit spot_light_class(openvrml::browser & browser);
        virtual ~spot_light_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Switch nodes.
     */
    class OPENVRML_LOCAL switch_class : public node_class {
    public:
        explicit switch_class(openvrml::browser & browser);
        virtual ~switch_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Text nodes.
     */
    class OPENVRML_LOCAL text_class : public node_class {
    public:
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        FT_Library freeTypeLibrary;
# endif

        explicit text_class(openvrml::browser & browser);
        virtual ~text_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for TextureCoordinate nodes.
     */
    class OPENVRML_LOCAL texture_coordinate_class : public node_class {
    public:
        explicit texture_coordinate_class(openvrml::browser & browser);
        virtual ~texture_coordinate_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for TextureTransform nodes.
     */
    class OPENVRML_LOCAL texture_transform_class : public node_class {
    public:
        explicit texture_transform_class(openvrml::browser & browser);
        virtual ~texture_transform_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for TimeSensor nodes.
     */
    class OPENVRML_LOCAL time_sensor_class : public node_class {
    public:
        explicit time_sensor_class(openvrml::browser & browser);
        virtual ~time_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for TouchSensor nodes.
     */
    class OPENVRML_LOCAL touch_sensor_class : public node_class {
    public:
        explicit touch_sensor_class(openvrml::browser & browser);
        virtual ~touch_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for Transform nodes.
     */
    class OPENVRML_LOCAL transform_class : public node_class {
    public:
        explicit transform_class(openvrml::browser & browser);
        virtual ~transform_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    class viewpoint_node;

    /**
     * @brief Class object for Viewpoint nodes.
     */
    class OPENVRML_LOCAL viewpoint_class : public node_class {
        typedef std::vector<viewpoint_node *> bound_nodes_t;

        viewpoint_node * first;
        bound_nodes_t bound_nodes;

    public:
        explicit viewpoint_class(openvrml::browser & browser);
        virtual ~viewpoint_class() throw ();

        void set_first(viewpoint_node & viewpoint) throw ();
        void reset_first() throw ();
        bool has_first() const throw ();
        bool is_first(viewpoint_node & viewpoint) throw ();
        void bind(viewpoint_node & viewpoint, double timestamp)
            throw (std::bad_alloc);
        void unbind(viewpoint_node & viewpoint, double timestamp) throw ();

    private:
        virtual void
        do_initialize(openvrml::viewpoint_node * initial_viewpoint,
                      double timestamp)
            throw ();
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for VisibilitySensor nodes.
     */
    class OPENVRML_LOCAL visibility_sensor_class : public node_class {
    public:
        explicit visibility_sensor_class(openvrml::browser & browser);
        virtual ~visibility_sensor_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };


    /**
     * @brief Class object for WorldInfo nodes.
     */
    class OPENVRML_LOCAL world_info_class : public node_class {
    public:
        explicit world_info_class(openvrml::browser & browser);
        virtual ~world_info_class() throw ();

    private:
        virtual const boost::shared_ptr<node_type>
        do_create_type(const std::string & id,
                       const node_interface_set & interfaces) const
            throw (unsupported_interface, std::bad_alloc);
    };
}

void register_node_classes(openvrml::browser & b)
{
    using boost::shared_ptr;
    using openvrml::node_class;
    b.add_node_class("urn:X-openvrml:node:Anchor",
                     shared_ptr<node_class>(new anchor_class(b)));
    b.add_node_class("urn:X-openvrml:node:Appearance",
                     shared_ptr<node_class>(new appearance_class(b)));
    b.add_node_class("urn:X-openvrml:node:AudioClip",
                     shared_ptr<node_class>(new audio_clip_class(b)));
    b.add_node_class("urn:X-openvrml:node:Background",
                     shared_ptr<node_class>(new background_class(b)));
    b.add_node_class("urn:X-openvrml:node:Billboard",
                     shared_ptr<node_class>(new billboard_class(b)));
    b.add_node_class("urn:X-openvrml:node:Box",
                     shared_ptr<node_class>(new box_class(b)));
    b.add_node_class("urn:X-openvrml:node:Collision",
                     shared_ptr<node_class>(new collision_class(b)));
    b.add_node_class("urn:X-openvrml:node:Color",
                     shared_ptr<node_class>(new color_class(b)));
    b.add_node_class("urn:X-openvrml:node:ColorInterpolator",
                     shared_ptr<node_class>(new color_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:Cone",
                     shared_ptr<node_class>(new cone_class(b)));
    b.add_node_class("urn:X-openvrml:node:Coordinate",
                     shared_ptr<node_class>(new coordinate_class(b)));
    b.add_node_class("urn:X-openvrml:node:CoordinateInterpolator",
                     shared_ptr<node_class>(
                         new coordinate_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:Cylinder",
                     shared_ptr<node_class>(new cylinder_class(b)));
    b.add_node_class("urn:X-openvrml:node:CylinderSensor",
                     shared_ptr<node_class>(new cylinder_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:DirectionalLight",
                     shared_ptr<node_class>(new directional_light_class(b)));
    b.add_node_class("urn:X-openvrml:node:ElevationGrid",
                     shared_ptr<node_class>(new elevation_grid_class(b)));
    b.add_node_class("urn:X-openvrml:node:Extrusion",
                     shared_ptr<node_class>(new extrusion_class(b)));
    b.add_node_class("urn:X-openvrml:node:Fog",
                     shared_ptr<node_class>(new fog_class(b)));
    b.add_node_class("urn:X-openvrml:node:FontStyle",
                     shared_ptr<node_class>(new font_style_class(b)));
    b.add_node_class("urn:X-openvrml:node:Group",
                     shared_ptr<node_class>(new group_class(b)));
    b.add_node_class("urn:X-openvrml:node:ImageTexture",
                     shared_ptr<node_class>(new image_texture_class(b)));
    b.add_node_class("urn:X-openvrml:node:IndexedFaceSet",
                     shared_ptr<node_class>(new indexed_face_set_class(b)));
    b.add_node_class("urn:X-openvrml:node:IndexedLineSet",
                     shared_ptr<node_class>(new indexed_line_set_class(b)));
    b.add_node_class("urn:X-openvrml:node:Inline",
                     shared_ptr<node_class>(new inline_class(b)));
    b.add_node_class("urn:X-openvrml:node:LOD",
                     shared_ptr<node_class>(new lod_class(b)));
    b.add_node_class("urn:X-openvrml:node:Material",
                     shared_ptr<node_class>(new material_class(b)));
    b.add_node_class("urn:X-openvrml:node:MovieTexture",
                     shared_ptr<node_class>(new movie_texture_class(b)));
    b.add_node_class("urn:X-openvrml:node:NavigationInfo",
                     shared_ptr<node_class>(new navigation_info_class(b)));
    b.add_node_class("urn:X-openvrml:node:Normal",
                     shared_ptr<node_class>(new normal_class(b)));
    b.add_node_class("urn:X-openvrml:node:NormalInterpolator",
                     shared_ptr<node_class>(new normal_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:OrientationInterpolator",
                     shared_ptr<node_class>(
                         new orientation_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:PixelTexture",
                     shared_ptr<node_class>(new pixel_texture_class(b)));
    b.add_node_class("urn:X-openvrml:node:PlaneSensor",
                     shared_ptr<node_class>(new plane_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:PointLight",
                     shared_ptr<node_class>(new point_light_class(b)));
    b.add_node_class("urn:X-openvrml:node:PointSet",
                     shared_ptr<node_class>(new point_set_class(b)));
    b.add_node_class("urn:X-openvrml:node:PositionInterpolator",
                     shared_ptr<node_class>(
                         new position_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:ProximitySensor",
                     shared_ptr<node_class>(new proximity_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:ScalarInterpolator",
                     shared_ptr<node_class>(new scalar_interpolator_class(b)));
    b.add_node_class("urn:X-openvrml:node:Shape",
                     shared_ptr<node_class>(new shape_class(b)));
    b.add_node_class("urn:X-openvrml:node:Sound",
                     shared_ptr<node_class>(new sound_class(b)));
    b.add_node_class("urn:X-openvrml:node:Sphere",
                     shared_ptr<node_class>(new sphere_class(b)));
    b.add_node_class("urn:X-openvrml:node:SphereSensor",
                     shared_ptr<node_class>(new sphere_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:SpotLight",
                     shared_ptr<node_class>(new spot_light_class(b)));
    b.add_node_class("urn:X-openvrml:node:Switch",
                     shared_ptr<node_class>(new switch_class(b)));
    b.add_node_class("urn:X-openvrml:node:Text",
                     shared_ptr<node_class>(new text_class(b)));
    b.add_node_class("urn:X-openvrml:node:TextureCoordinate",
                     shared_ptr<node_class>(new texture_coordinate_class(b)));
    b.add_node_class("urn:X-openvrml:node:TextureTransform",
                     shared_ptr<node_class>(new texture_transform_class(b)));
    b.add_node_class("urn:X-openvrml:node:TimeSensor",
                     shared_ptr<node_class>(new time_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:TouchSensor",
                     shared_ptr<node_class>(new touch_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:Transform",
                     shared_ptr<node_class>(new transform_class(b)));
    b.add_node_class("urn:X-openvrml:node:Viewpoint",
                     shared_ptr<node_class>(new viewpoint_class(b)));
    b.add_node_class("urn:X-openvrml:node:VisibilitySensor",
                     shared_ptr<node_class>(new visibility_sensor_class(b)));
    b.add_node_class("urn:X-openvrml:node:WorldInfo",
                     shared_ptr<node_class>(new world_info_class(b)));
}

namespace {

    using namespace openvrml_;

    /**
     * @brief Abstract base class for IndexedFaceSet and IndexedLineSet.
     */
    template <typename Derived>
    class OPENVRML_LOCAL abstract_indexed_set_node :
        public abstract_node<Derived>,
        public geometry_node {
    protected:
        typedef typename abstract_node<Derived>::self_t self_t;

        class set_color_index_listener :
            public event_listener_base<self_t>,
            public abstract_node<Derived>::mfint32_listener {
        public:
            explicit set_color_index_listener(
                abstract_indexed_set_node & node);
            virtual ~set_color_index_listener() throw ();

        private:
            virtual void do_process_event(const mfint32 & color_index,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class set_coord_index_listener :
            public event_listener_base<self_t>,
            public abstract_node<Derived>::mfint32_listener {
        public:
            explicit set_coord_index_listener(
                abstract_indexed_set_node & node);
            virtual ~set_coord_index_listener() throw ();

        private:
            virtual void do_process_event(const mfint32 & coord_index,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_color_index_listener set_color_index_;
        set_coord_index_listener set_coord_index_;
        typename abstract_node<Derived>::
        template exposedfield<sfnode> color_;
        typename abstract_node<Derived>::
        template exposedfield<sfnode> coord_;
        mfint32 color_index_;
        sfbool color_per_vertex_;
        mfint32 coord_index_;

    public:
        virtual ~abstract_indexed_set_node() throw () = 0;

        virtual bool modified() const;

        virtual const openvrml::color_node * color() const throw ();

    protected:
        abstract_indexed_set_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
    };

    /**
     * @internal
     *
     * @class abstract_indexed_set_node::set_color_index_listener
     *
     * @brief set_colorIndex event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  abstract_indexed_set_node.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::set_color_index_listener::
    set_color_index_listener(abstract_indexed_set_node & node):
        node_event_listener(node),
        event_listener_base<Derived>(node),
        abstract_node<Derived>::mfint32_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::set_color_index_listener::
    ~set_color_index_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param color_index colorIndex.
     * @param timestamp   the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    template <typename Derived>
    void
    abstract_indexed_set_node<Derived>::set_color_index_listener::
    do_process_event(const mfint32 & color_index, double)
        throw (std::bad_alloc)
    {
        abstract_indexed_set_node * abstract_indexed_set =
            dynamic_cast<abstract_indexed_set_node *>(&this->node());
        assert(abstract_indexed_set);
        abstract_indexed_set->color_index_ = color_index;
        abstract_indexed_set->node::modified(true);
    }

    /**
     * @internal
     *
     * @class abstract_indexed_set_node::set_coord_index_listener
     *
     * @brief set_coordIndex event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  abstract_indexed_set_node.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::set_coord_index_listener::
    set_coord_index_listener(abstract_indexed_set_node & node):
        node_event_listener(node),
        event_listener_base<Derived>(node),
        abstract_node<Derived>::mfint32_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::set_coord_index_listener::
    ~set_coord_index_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param coord_index coordIndex.
     * @param timestamp   the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    template <typename Derived>
    void
    abstract_indexed_set_node<Derived>::set_coord_index_listener::
    do_process_event(const mfint32 & coord_index, double)
        throw (std::bad_alloc)
    {
        abstract_indexed_set_node * abstract_indexed_set =
            dynamic_cast<abstract_indexed_set_node *>(&this->node());
        assert(abstract_indexed_set);
        abstract_indexed_set->coord_index_ = coord_index;
        abstract_indexed_set->node::modified(true);
    }

    /**
     * @var abstract_indexed_set_node<Derived>::set_color_index_listener abstract_indexed_set_node<Derived>::set_color_index_
     *
     * @brief set_colorIndex event handler.
     */

    /**
     * @var abstract_indexed_set_node<Derived>::set_coord_index_listener template abstract_indexed_set_node<Derived>::set_coord_index_
     *
     * @brief set_coordIndex event handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<openvrml::sfnode> abstract_indexed_set_node<Derived>::color_
     *
     * @brief color exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<sfnode> abstract_indexed_set_node<Derived>::coord_
     *
     * @brief coord exposedField.
     */

    /**
     * @var openvrml::mfint32 abstract_indexed_set_node<Derived>::color_index_
     *
     * @brief colorIndex field.
     */

    /**
     * @var openvrml::sfbool abstract_indexed_set_node<Derived>::color_per_vertex_
     *
     * @brief colorPerVertex field.
     */

    /**
     * @var openvrml::mfint32 abstract_indexed_set_node<Derived>::coord_index_
     *
     * @brief coordIndex field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::abstract_indexed_set_node(
        const node_type & type,
        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<Derived>(type, scope),
        geometry_node(type, scope),
        set_color_index_(*this),
        set_coord_index_(*this),
        color_(*this),
        coord_(*this),
        color_per_vertex_(true)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    abstract_indexed_set_node<Derived>::~abstract_indexed_set_node()
        throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    template <typename Derived>
    bool abstract_indexed_set_node<Derived>::modified() const
    {
        return this->node::modified()
            || (this->color_.sfnode::value()
                && this->color_.sfnode::value()->modified())
            || (this->coord_.sfnode::value()
                && this->coord_.sfnode::value()->modified());
    }

    /**
     * @brief color_node.
     *
     * @return the color_node, or 0 if none is set.
     */
    template <typename Derived>
    const openvrml::color_node *
    abstract_indexed_set_node<Derived>::color() const throw ()
    {
        return node_cast<openvrml::color_node *>(
            this->color_.sfnode::value().get());
    }


    /**
     * @brief Base class for all light nodes.
     */
    template <typename Derived>
    class OPENVRML_LOCAL abstract_light_node : public abstract_node<Derived>,
                                               public virtual light_node {
    protected:
        typename abstract_node<Derived>::template exposedfield<sffloat>
        ambient_intensity_;
        typename abstract_node<Derived>::template exposedfield<sfcolor>
        color_;
        typename abstract_node<Derived>::template exposedfield<sffloat>
        intensity_;
        typename abstract_node<Derived>::template exposedfield<sfbool> on_;

    public:
        virtual ~abstract_light_node() throw () = 0;

        float ambient_intensity() const throw ();
        float intensity() const throw ();
        bool on() const throw ();
        const openvrml::color & color() const throw ();

    protected:
        abstract_light_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
    };

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<openvrml::sffloat> abstract_light_node::ambient_intensity_
     *
     * @brief ambientIntensity exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<openvrml::sfcolor> abstract_light_node::color_
     *
     * @brief color exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<openvrml::sffloat> abstract_light_node::intensity_
     *
     * @brief intensity exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<Derived>::exposedfield<openvrml::sfbool> abstract_light_node::on_
     *
     * @brief on exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type for the node.
     * @param scope     the scope to which the node belongs.
     */
    template <typename Derived>
    abstract_light_node<Derived>::
    abstract_light_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        light_node(type, scope),
        abstract_node<Derived>(type, scope),
        ambient_intensity_(*this, 0.0),
        color_(*this, openvrml::color(1.0, 1.0, 1.0)),
        intensity_(*this, 1.0),
        on_(*this, true)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    abstract_light_node<Derived>::~abstract_light_node() throw ()
    {}

    /**
     * @brief Ambient intensity.
     *
     * @return the ambient intensity.
     */
    template <typename Derived>
    float abstract_light_node<Derived>::ambient_intensity() const throw ()
    {
        return this->ambient_intensity_.sffloat::value;
    }

    /**
     * @brief Intensity.
     *
     * @return the intensity.
     */
    template <typename Derived>
    float abstract_light_node<Derived>::intensity() const throw ()
    {
        return this->intensity_.sffloat::value;
    }

    /**
     * @brief Whether the light is on.
     *
     * @return @c true if the light is on; @c false otherwise.
     */
    template <typename Derived>
    bool abstract_light_node<Derived>::on() const throw ()
    {
        return this->on_.sfbool::value;
    }

    /**
     * @brief Light color.
     *
     * @return the light color.
     */
    template <typename Derived>
    const openvrml::color &
    abstract_light_node<Derived>::color() const throw ()
    {
        return this->color_.sfcolor::value;
    }


    /**
     * @brief Abstract base class for VRML97 texture nodes.
     */
    template <typename Derived>
    class OPENVRML_LOCAL abstract_texture_node :
        public abstract_node<Derived>,
        public texture_node {
    protected:
        sfbool repeat_s_;
        sfbool repeat_t_;

    public:
        virtual ~abstract_texture_node() throw () = 0;

        //
        // texture_node implementation.
        //
        virtual bool repeat_s() const throw ();
        virtual bool repeat_t() const throw ();

    protected:
        abstract_texture_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
    };

    /**
     * @var openvrml::sfbool abstract_texture_node::repeat_s_
     *
     * @brief repeatS field.
     */

    /**
     * @var openvrml::sfbool abstract_texture_node::repeat_t_
     *
     * @brief repeatT field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type for the node instance.
     * @param scope the scope to which the node belongs.
     */
    template <typename Derived>
    abstract_texture_node<Derived>::
    abstract_texture_node(
        const node_type & type,
        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<Derived>(type, scope),
        texture_node(type, scope),
        repeat_s_(true),
        repeat_t_(true)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    abstract_texture_node<Derived>::~abstract_texture_node() throw ()
    {}

    /**
     * @brief Get the repeatS flag.
     *
     * @return @c true if the texture should repeat in the <var>S</var>
     *         direction, @c false otherwise.
     */
    template <typename Derived>
    bool abstract_texture_node<Derived>::repeat_s() const throw ()
    {
        return this->repeat_s_.value();
    }

    /**
     * @brief Get the repeatT flag.
     *
     * @return @c true if the texture should repeat in the <var>T</var>
     *         direction, @c false otherwise.
     */
    template <typename Derived>
    bool abstract_texture_node<Derived>::repeat_t() const throw ()
    {
        return this->repeat_t_.value();
    }


    /**
     * @brief Base class template for grouping nodes.
     */
    template <typename Derived>
    class OPENVRML_LOCAL grouping_node_base : public abstract_node<Derived>,
                                              public virtual grouping_node {
        typedef typename abstract_node<Derived>::self_t self_t;

    protected:
        class add_children_listener :
            public event_listener_base<self_t>,
            public abstract_node<Derived>::mfnode_listener {
        public:
            explicit add_children_listener(
                grouping_node_base<Derived> & node);
            virtual ~add_children_listener() throw ();

        private:
            virtual void do_process_event(const mfnode & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class remove_children_listener :
            public event_listener_base<self_t>,
            public abstract_node<Derived>::mfnode_listener {
        public:
            explicit remove_children_listener(
                grouping_node_base<Derived> & node);
            virtual ~remove_children_listener() throw ();

        private:
            virtual void do_process_event(const mfnode & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class children_exposedfield :
            public abstract_node<Derived>::template exposedfield<mfnode> {
        public:
            explicit children_exposedfield(openvrml::node & node) throw ();
            children_exposedfield(const children_exposedfield & obj) throw ();
            virtual ~children_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfnode & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        sfvec3f bbox_center_;
        sfvec3f bbox_size_;
        add_children_listener add_children_listener_;
        remove_children_listener remove_children_listener_;
        children_exposedfield children_;

        viewer::object_t viewerObject;

        bounding_sphere bsphere;

    public:
        grouping_node_base(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~grouping_node_base() throw ();

        virtual bool modified() const;

    protected:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;
        virtual const std::vector<boost::intrusive_ptr<node> > &
        do_children() const throw ();

        void recalc_bsphere();
        void render_nocull(openvrml::viewer & viewer,
                           rendering_context context);
    };

    /**
     * @internal
     *
     * @class grouping_node_base::add_children_listener
     *
     * @brief addChildren event listener.
     */

    /**
     * @brief Construct.
     *
     * @param node  a grouping node.
     */
    template <typename Derived>
    grouping_node_base<Derived>::add_children_listener::
    add_children_listener(grouping_node_base<Derived> & node):
        node_event_listener(node),
        event_listener_base<Derived>(node),
        abstract_node<Derived>::mfnode_listener(node)
    {}

   /**
    * @brief Destroy.
    */
    template <typename Derived>
    grouping_node_base<Derived>::add_children_listener::
    ~add_children_listener() throw ()
    {}

    /**
     * @brief Process an event.
     *
     * If this function throws, it is possible (even likely) that only part of
     * the nodes in @p value have been added to the Group node's children
     * exposedField.
     *
     * @param value     @link openvrml::child_node child_nodes@endlink to add.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc        if memory allocation fails.
     */
    template <typename Derived>
    void
    grouping_node_base<Derived>::add_children_listener::
    do_process_event(const mfnode & value, const double timestamp)
        throw (std::bad_alloc)
    {
        Derived & group = dynamic_cast<Derived &>(this->node());

        typedef std::vector<boost::intrusive_ptr<openvrml::node> > children_t;
        children_t children = group.children_.mfnode::value();

        for (children_t::const_iterator n = value.value().begin();
             n != value.value().end();
             ++n) {
            //
            // Don't add NULLs.
            //
            if (*n) {
                using std::find;

                children_t::iterator pos =
                    find(children.begin(), children.end(), *n);
                if (pos == children.end()) {
                    //
                    // Throws std::bad_alloc.
                    //
                    children.push_back(*n);
                    scope_guard guard =
                        make_obj_guard(children, &children_t::pop_back);
                    child_node * const child =
                        node_cast<child_node *>(n->get());
                    if (child) {
                        child->relocate(); // Throws std::bad_alloc.
                    }
                    guard.dismiss();
                }
            }
        }

        group.children_.mfnode::value(children);

        group.node::modified(true);
        group.bounding_volume_dirty(true);
        node::emit_event(group.children_, timestamp);
    }

    /**
     * @internal
     *
     * @class grouping_node_base::remove_children_listener
     *
     * @brief removeChildren event listener.
     */

    /**
     * @brief Construct.
     *
     * @param node  a grouping node.
     */
    template <typename Derived>
    grouping_node_base<Derived>::
    remove_children_listener::
    remove_children_listener(grouping_node_base<Derived> & node):
        node_event_listener(node),
        event_listener_base<Derived>(node),
        abstract_node<Derived>::mfnode_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    grouping_node_base<Derived>::remove_children_listener::
    ~remove_children_listener() throw ()
    {}

    /**
     * @brief Process an event.
     */
    template <typename Derived>
    void
    grouping_node_base<Derived>::remove_children_listener::
    do_process_event(const mfnode & value, const double timestamp)
        throw (std::bad_alloc)
    {
        self_t & group = dynamic_cast<self_t &>(this->node());

        typedef std::vector<boost::intrusive_ptr<openvrml::node> > children_t;
        children_t children = group.children_.mfnode::value();

        for (children_t::const_iterator n = value.value().begin();
             n != value.value().end();
             ++n) {
            using std::remove;
            children.erase(remove(children.begin(), children.end(), *n),
                           children.end());
        }

        group.children_.mfnode::value(children);

        group.node::modified(true);
        group.bounding_volume_dirty(true);
        node::emit_event(group.children_, timestamp);
    }

    /**
     * @internal
     *
     * @class grouping_node_base::children_exposedfield
     *
     * @brief children exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  group_node.
     */
    template <typename Derived>
    grouping_node_base<Derived>::children_exposedfield::
    children_exposedfield(openvrml::node & node) throw ():
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        abstract_node<Derived>::mfnode_listener(node),
        abstract_node<Derived>::template exposedfield<openvrml::mfnode>(
            node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    template <typename Derived>
    grouping_node_base<Derived>::children_exposedfield::
    children_exposedfield(const children_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        abstract_node<Derived>::mfnode_listener(
            obj.node_event_listener::node()),
        abstract_node<Derived>::template exposedfield<openvrml::mfnode>(obj)
    {}

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    grouping_node_base<Derived>::children_exposedfield::
    ~children_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     */
    template <typename Derived>
    std::auto_ptr<openvrml::field_value>
    grouping_node_base<Derived>::children_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new children_exposedfield(*this));
    }

    /**
     * @brief Handle event.
     */
    template <typename Derived>
    void
    grouping_node_base<Derived>::children_exposedfield::
    event_side_effect(const mfnode & value, double)
        throw (std::bad_alloc)
    {
        self_t & group =
            dynamic_cast<self_t &>(this->node_event_listener::node());

        typedef std::vector<boost::intrusive_ptr<openvrml::node> > children_t;
        children_t children;

        for (children_t::const_iterator n = value.value().begin();
             n != value.value().end();
             ++n) {
            //
            // The spec is ambiguous about whether the children field of
            // grouping nodes can contain NULLs. We allow it; for now, at
            // least.
            //
            children.push_back(*n); // Throws std::bad_alloc.
            scope_guard guard =
                make_obj_guard(children, &children_t::pop_back);
            child_node * const child =
                node_cast<child_node *>(n->get());
            if (child) { child->relocate(); } // Throws std::bad_alloc.
            guard.dismiss();
        }

        this->mfnode::value(children);

        group.bounding_volume_dirty(true);
    }

    /**
     * @var openvrml::sfvec3f grouping_node_base::bbox_center_
     *
     * @brief bboxCenter field.
     */

    /**
     * @var openvrml::sfvec3f grouping_node_base::bbox_size_
     *
     * @brief bboxSize field.
     */

    /**
     * @var grouping_node_base::add_children_listener grouping_node_base::add_children_listener_
     *
     * @brief addChildren eventIn handler.
     */

    /**
     * @var grouping_node_base::remove_children_listener grouping_node_base::remove_children_listener_
     *
     * @brief removeChildren eventIn handler.
     */

    /**
     * @var grouping_node_base::children_exposedfield grouping_node_base::children_
     *
     * @brief children exposedField.
     */

    /**
     * @var openvrml::viewer::object_t grouping_node_base::viewerObject
     *
     * @brief Handle for the renderer.
     */

    /**
     * @var bounding_sphere grouping_node_base::bsphere
     *
     * @brief Cached copy of the bounding_sphere enclosing this node's children.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope the scope to which the node belongs.
     */
    template <typename Derived>
    grouping_node_base<Derived>::
    grouping_node_base(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        abstract_node<Derived>(type, scope),
        bbox_size_(vec3f(-1.0, -1.0, -1.0)),
        add_children_listener_(*this),
        remove_children_listener_(*this),
        children_(*this),
        viewerObject(0)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    template <typename Derived>
    grouping_node_base<Derived>::~grouping_node_base() throw ()
    {
        // delete viewerObject...
    }

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    template <typename Derived>
    bool grouping_node_base<Derived>::modified() const
    {
        if (this->node::modified()) { return true; }
        for (size_t i = 0; i < this->children_.mfnode::value().size(); ++i) {
            if (this->children_.mfnode::value()[i]->modified()) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Render the node.
     *
     * Render each of the children.
     *
     * @param viewer    a Viewer.
     * @param context   a rendering context.
     */
    template <typename Derived>
    void
    grouping_node_base<Derived>::
    do_render_child(openvrml::viewer & viewer, rendering_context context)
    {
        if (context.cull_flag != bounding_volume::inside) {
            assert(dynamic_cast<const bounding_sphere *>
                   (&this->bounding_volume()));
            const bounding_sphere & bs =
                static_cast<const bounding_sphere &>(
                    this->bounding_volume());
            bounding_sphere bv_copy(bs);
            bv_copy.transform(context.matrix());
            bounding_volume::intersection r =
                viewer.intersect_view_volume(bv_copy);
            if (context.draw_bounding_spheres) {
                viewer.draw_bounding_sphere(bs, r);
            }
            if (r == bounding_volume::outside) { return; }
            if (r == bounding_volume::inside) {
                context.cull_flag = bounding_volume::inside;
            }
        }
        this->render_nocull(viewer, context);
    }

    /**
     * because children will already have done the culling, we don't need
     * to repeat it here.
     */
    template <typename Derived>
    void
    grouping_node_base<Derived>::render_nocull(openvrml::viewer & viewer,
                                               rendering_context context)
    {
        using std::vector;

        if (this->viewerObject && this->modified()) {
            viewer.remove_object(this->viewerObject);
            this->viewerObject = 0;
        }

        if (this->viewerObject) {
            viewer.insert_reference(this->viewerObject);
        } else if (!this->children_.mfnode::value().empty()) {
            vector<boost::intrusive_ptr<node> >::size_type i;
            vector<boost::intrusive_ptr<node> >::size_type n =
                this->children_.mfnode::value().size();
            size_t nSensors = 0;

            this->viewerObject = viewer.begin_object(this->id().c_str());

            // Draw nodes that impact their siblings (DirectionalLights,
            // TouchSensors, any others? ...)
            for (i = 0; i < n; ++i) {
                child_node * const child =
                    node_cast<child_node *>(
                        this->children_.mfnode::value()[i].get());
                if (child) {
                    if (node_cast<light_node *>(child)
                        && !(node_cast<scoped_light_node *>(child))) {
                        child->render_child(viewer, context);
                    } else if (
                        node_cast<pointing_device_sensor_node *>(child)) {
                        if (++nSensors == 1) {
                            viewer.set_sensitive(this);
                        }
                    }
                }
            }

            // Do the rest of the children (except the scene-level lights)
            for (i = 0; i<n; ++i) {
                child_node * const child =
                    node_cast<child_node *>(
                        this->children_.mfnode::value()[i].get());
                if (child && !(node_cast<light_node *>(child))) {
                    child->render_child(viewer, context);
                }
            }

            // Turn off sensitivity
            if (nSensors > 0) { viewer.set_sensitive(0); }

            viewer.end_object();
        }

        this->node::modified(false);
    }

    /**
     * @brief Get the children in the scene graph.
     *
     * @return the child nodes in the scene graph.
     */
    template <typename Derived>
    const std::vector<boost::intrusive_ptr<openvrml::node> > &
    grouping_node_base<Derived>::do_children() const throw ()
    {
        return this->children_.mfnode::value();
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    template <typename Derived>
    const openvrml::bounding_volume &
    grouping_node_base<Derived>::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<grouping_node_base<Derived> *>(this)
                ->recalc_bsphere();
        }
        return this->bsphere;
    }

    /**
     * @fn void grouping_node_base<Derived>::recalc_bsphere()
     *
     * @brief Recalculate the bounding volume.
     */
    template <typename Derived>
    void grouping_node_base<Derived>::recalc_bsphere()
    {
        this->bsphere = bounding_sphere();
        for (size_t i = 0; i < this->children_.mfnode::value().size(); ++i) {
            const boost::intrusive_ptr<node> & node = this->children_.mfnode::value()[i];
            bounded_volume_node * bounded_volume =
                node_cast<bounded_volume_node *>(node.get());
            if (bounded_volume) {
                const openvrml::bounding_volume & ci_bv =
                    bounded_volume->bounding_volume();
                this->bsphere.extend(ci_bv);
            }
        }
        this->bounding_volume_dirty(false);
    }


    class OPENVRML_LOCAL anchor_node : public grouping_node_base<anchor_node>,
                                       public pointing_device_sensor_node {
        friend class anchor_class;

        exposedfield<sfstring> description_;
        exposedfield<mfstring> parameter_;
        exposedfield<mfstring> url_;

    public:
        anchor_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~anchor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };


    class OPENVRML_LOCAL appearance_node :
        public abstract_node<appearance_node>,
        public openvrml::appearance_node {

        friend class appearance_class;

        exposedfield<sfnode> material_;
        exposedfield<sfnode> texture_;
        exposedfield<sfnode> texture_transform_;

    public:
        appearance_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~appearance_node() throw ();

        virtual bool modified() const;

        //
        // appearance_node implementation
        //
        virtual const boost::intrusive_ptr<node> & material() const throw ();
        virtual const boost::intrusive_ptr<node> & texture() const throw ();
        virtual const boost::intrusive_ptr<node> & texture_transform() const throw ();

    private:
        virtual void do_render_appearance(viewer & v,
                                          rendering_context context);
    };


    class OPENVRML_LOCAL audio_clip_node :
        public abstract_node<audio_clip_node>,
        public time_dependent_node {

        friend class audio_clip_class;

        exposedfield<sfstring> description_;
        exposedfield<sfbool> loop_;
        exposedfield<sffloat> pitch_;
        exposedfield<sftime> start_time_;
        exposedfield<sftime> stop_time_;
        exposedfield<mfstring> url_;
        sftime duration_changed_;
        sftime_emitter duration_changed_emitter_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;

    public:
        audio_clip_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~audio_clip_node() throw ();

    private:
        virtual void do_initialize(double timestamp) throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();
        virtual void do_update(double time);
    };


    class OPENVRML_LOCAL background_node :
        public abstract_node<background_node>,
        public child_node {

        friend class background_class;

        class set_bind_listener : public event_listener_base<self_t>,
                                  public sfbool_listener {
        public:
            explicit set_bind_listener(background_node & node);
            virtual ~set_bind_listener() throw ();

        private:
            virtual void do_process_event(const sfbool & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class back_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit back_url_exposedfield(background_node & node) throw ();
            back_url_exposedfield(const back_url_exposedfield & obj) throw ();
            virtual ~back_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class bottom_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit bottom_url_exposedfield(background_node & node) throw ();
            bottom_url_exposedfield(const bottom_url_exposedfield & obj)
                throw ();
            virtual ~bottom_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class front_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit front_url_exposedfield(background_node & node) throw ();
            front_url_exposedfield(const front_url_exposedfield & obj)
                throw ();
            virtual ~front_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class left_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit left_url_exposedfield(background_node & node) throw ();
            left_url_exposedfield(const left_url_exposedfield & obj) throw ();
            virtual ~left_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class right_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit right_url_exposedfield(background_node & node) throw ();
            right_url_exposedfield(const right_url_exposedfield & obj)
                throw ();
            virtual ~right_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class top_url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit top_url_exposedfield(background_node & node) throw ();
            top_url_exposedfield(const top_url_exposedfield & obj) throw ();
            virtual ~top_url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & value,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        set_bind_listener set_bind_listener_;
        exposedfield<mffloat> ground_angle_;
        exposedfield<mfcolor> ground_color_;
        back_url_exposedfield back_url_;
        bottom_url_exposedfield bottom_url_;
        front_url_exposedfield front_url_;
        left_url_exposedfield left_url_;
        right_url_exposedfield right_url_;
        top_url_exposedfield top_url_;
        exposedfield<mffloat> sky_angle_;
        exposedfield<mfcolor> sky_color_;
        sfbool is_bound_;
        sfbool_emitter is_bound_emitter_;

        image front;
        bool front_needs_update;
        image back;
        bool back_needs_update;
        image left;
        bool left_needs_update;
        image right;
        bool right_needs_update;
        image top;
        bool top_needs_update;
        image bottom;
        bool bottom_needs_update;

        // Display list object for background
        viewer::object_t viewerObject;

    public:
        background_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~background_node() throw ();

    private:
        virtual void do_initialize(double timestamp) throw ();
        virtual void do_shutdown(double timestamp) throw ();

        void update_textures();
    };


    class OPENVRML_LOCAL billboard_node :
        public grouping_node_base<billboard_node> {
        friend class billboard_class;

        exposedfield<sfvec3f> axis_of_rotation_;

        viewer::object_t xformObject;

    public:
        static const mat4f billboard_to_matrix(const billboard_node & node,
                                               const mat4f & modelview);

        billboard_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~billboard_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL box_node : public abstract_node<box_node>,
                                    public geometry_node {
        friend class box_class;

        sfvec3f size;

        bounding_sphere bsphere;

    public:
        box_node(const node_type & type,
                 const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~box_node() throw ();

    private:
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;

        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL collision_node :
        public grouping_node_base<collision_node> {

        friend class collision_class;

        exposedfield<sfbool> collide_;
        sfnode proxy_;
        sftime collide_time_;
        sftime_emitter collide_time_emitter_;

    public:
        collision_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~collision_node() throw ();

        virtual bool modified() const;
    };


    class OPENVRML_LOCAL color_node : public abstract_node<color_node>,
                                      public openvrml::color_node {
        friend class color_class;

        exposedfield<mfcolor> color_;

    public:
        color_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~color_node() throw ();

        //
        // color_node implementation
        //
        virtual const std::vector<openvrml::color> & color() const
            throw ();
    };


    class OPENVRML_LOCAL color_interpolator_node :
        public abstract_node<color_interpolator_node>,
        public child_node {

        friend class color_interpolator_class;

        class set_fraction_listener :
            public event_listener_base<self_t>,
            public sffloat_listener {
        public:
            explicit set_fraction_listener(color_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfcolor> key_value_;
        sfcolor value_;
        sfcolor_emitter value_changed_;

    public:
        color_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~color_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL cone_node : public abstract_node<cone_node>,
                                     public geometry_node {
        friend class cone_class;

        sfbool bottom;
        sffloat bottomRadius;
        sffloat height;
        sfbool side;

    public:
        cone_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~cone_node() throw ();

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL coordinate_node :
        public abstract_node<coordinate_node>,
        public openvrml::coordinate_node {

        friend class coordinate_class;

        exposedfield<mfvec3f> point_;

    public:
        coordinate_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~coordinate_node() throw ();

        //
        // coordinate_node implementation
        //
        virtual const std::vector<vec3f> & point() const throw ();
    };


    class OPENVRML_LOCAL coordinate_interpolator_node :
        public abstract_node<coordinate_interpolator_node>,
        public child_node {

        friend class coordinate_interpolator_class;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(
                coordinate_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfvec3f> key_value_;
        mfvec3f value_;
        mfvec3f_emitter value_changed_;

    public:
        coordinate_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~coordinate_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL cylinder_node : public abstract_node<cylinder_node>,
                                         public geometry_node {
        friend class cylinder_class;

        sfbool bottom;
        sffloat height;
        sffloat radius;
        sfbool side;
        sfbool top;

    public:
        cylinder_node(const node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~cylinder_node() throw ();

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL cylinder_sensor_node :
        public abstract_node<cylinder_sensor_node>,
        public pointing_device_sensor_node {

        friend class cylinder_sensor_class;

        exposedfield<sfbool> auto_offset_;
        exposedfield<sffloat> disk_angle_;
        exposedfield<sfbool> enabled_;
        exposedfield<sffloat> max_angle_;
        exposedfield<sffloat> min_angle_;
        exposedfield<sffloat> offset_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfrotation rotation_changed_;
        sfrotation_emitter rotation_changed_emitter_;
        sfvec3f track_point_changed_;
        sfvec3f_emitter track_point_changed_emitter_;

        float rotation_val;
        vec3f activationPoint;
        bool disk;
        mat4f activationMatrix;
        mat4f modelview;

    public:
        cylinder_sensor_node(const node_type & type,
                             const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~cylinder_sensor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };


    class OPENVRML_LOCAL directional_light_node :
        public abstract_light_node<directional_light_node> {

        friend class directional_light_class;

        exposedfield<sfvec3f> direction_;

    public:
        directional_light_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~directional_light_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL elevation_grid_node :
        public abstract_node<elevation_grid_node>,
        public geometry_node {

        friend class elevation_grid_class;

        class set_height_listener : public event_listener_base<self_t>,
                                    public mffloat_listener {
        public:
            explicit set_height_listener(elevation_grid_node & node);
            virtual ~set_height_listener() throw ();

        private:
            virtual void do_process_event(const mffloat & height,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_height_listener set_height_listener_;
        exposedfield<sfnode> color_;
        exposedfield<sfnode> normal_;
        exposedfield<sfnode> tex_coord_;
        mffloat height_;
        sfbool ccw_;
        sfbool color_per_vertex_;
        sffloat crease_angle_;
        sfbool normal_per_vertex_;
        sfbool solid_;
        sfint32 x_dimension_;
        sffloat x_spacing_;
        sfint32 z_dimension_;
        sffloat z_spacing_;

    public:
        elevation_grid_node(const node_type & type,
                            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~elevation_grid_node() throw ();

        virtual bool modified() const;

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL extrusion_node : public abstract_node<extrusion_node>,
                                          public geometry_node {

        friend class extrusion_class;

        class set_cross_section_listener :
            public event_listener_base<self_t>,
            public mfvec2f_listener {
        public:
            explicit set_cross_section_listener(extrusion_node & node);
            virtual ~set_cross_section_listener() throw ();

        private:
            virtual void do_process_event(const mfvec2f & cross_section,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class set_orientation_listener : public event_listener_base<self_t>,
                                         public mfrotation_listener {
        public:
            explicit set_orientation_listener(extrusion_node & node);
            virtual ~set_orientation_listener() throw ();

        private:
            virtual void do_process_event(const mfrotation & orientation,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class set_scale_listener : public event_listener_base<self_t>,
                                   public mfvec2f_listener {
        public:
            explicit set_scale_listener(extrusion_node & node);
            virtual ~set_scale_listener() throw ();

        private:
            virtual void do_process_event(const mfvec2f & scale,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class set_spine_listener : public event_listener_base<self_t>,
                                   public mfvec3f_listener {
        public:
            explicit set_spine_listener(extrusion_node & node);
            virtual ~set_spine_listener() throw ();

        private:
            virtual void do_process_event(const mfvec3f & spine,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_cross_section_listener set_cross_section_listener_;
        set_orientation_listener set_orientation_listener_;
        set_scale_listener set_scale_listener_;
        set_spine_listener set_spine_listener_;
        sfbool begin_cap_;
        sfbool ccw_;
        sfbool convex_;
        sffloat crease_angle_;
        mfvec2f cross_section_;
        sfbool end_cap_;
        mfrotation orientation_;
        mfvec2f scale_;
        sfbool solid_;
        mfvec3f spine_;

    public:
        extrusion_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~extrusion_node() throw ();

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL fog_node : public abstract_node<fog_node>,
                                    public child_node {
        friend class fog_class;

        class set_bind_listener : public event_listener_base<self_t>,
                                  public sfbool_listener {
        public:
            explicit set_bind_listener(fog_node & node);
            virtual ~set_bind_listener() throw ();

        private:
            virtual void do_process_event(const sfbool & bind,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_bind_listener set_bind_listener_;
        exposedfield<sfcolor> color_;
        exposedfield<sfstring> fog_type_;
        exposedfield<sffloat> visibility_range_;
        sfbool is_bound_;
        sfbool_emitter is_bound_emitter_;

    public:
        fog_node(const node_type & type,
                 const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~fog_node() throw ();

    private:
        virtual void do_initialize(double timestamp) throw ();
        virtual void do_shutdown(double timestamp) throw ();
    };


    class OPENVRML_LOCAL font_style_node :
        public abstract_node<font_style_node>,
        public openvrml::font_style_node {

        friend class font_style_class;

        mfstring family_;
        sfbool horizontal_;
        mfstring justify_;
        sfstring language_;
        sfbool leftToRight;
        sffloat size_;
        sffloat spacing_;
        sfstring style_;
        sfbool topToBottom;

    public:
        font_style_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~font_style_node() throw ();

        //
        // font_style_node implementation
        //
        virtual const std::vector<std::string> & family() const throw ();
        virtual bool horizontal() const throw ();
        virtual const std::vector<std::string> & justify() const throw ();
        virtual const std::string & language() const throw ();
        virtual bool left_to_right() const throw ();
        virtual float size() const throw ();
        virtual float spacing() const throw ();
        virtual const std::string & style() const throw ();
        virtual bool top_to_bottom() const throw ();
    };


    class OPENVRML_LOCAL group_node : public grouping_node_base<group_node> {
        friend class group_class;

    public:
        group_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~group_node() throw ();
    };


    class OPENVRML_LOCAL image_texture_node :
        public abstract_texture_node<image_texture_node> {

        friend class image_texture_class;

        class url_exposedfield : public exposedfield<mfstring> {
        public:
            explicit url_exposedfield(image_texture_node & node);
            url_exposedfield(const url_exposedfield & obj) throw ();
            virtual ~url_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & url,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        url_exposedfield url_;

        openvrml::image image_;
        bool texture_needs_update;

    public:
        image_texture_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~image_texture_node() throw ();

        virtual const openvrml::image & image() const throw ();

    private:
        virtual viewer::texture_object_t do_render_texture(viewer & v);

        void update_texture();
    };


    class OPENVRML_LOCAL indexed_face_set_node :
        public abstract_indexed_set_node<indexed_face_set_node> {

        friend class indexed_face_set_class;

        class set_normal_index_listener :
            public event_listener_base<self_t>,
            public mfint32_listener {
        public:
            explicit set_normal_index_listener(
                indexed_face_set_node & node);
            virtual ~set_normal_index_listener() throw ();

        private:
            virtual void do_process_event(const mfint32 & normal_index,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class set_tex_coord_index_listener :
            public event_listener_base<self_t>,
            public mfint32_listener {
        public:
            explicit set_tex_coord_index_listener(
                indexed_face_set_node & node);
            virtual ~set_tex_coord_index_listener() throw ();

        private:
            virtual void do_process_event(const mfint32 & tex_coord_index,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_normal_index_listener set_normal_index_listener_;
        set_tex_coord_index_listener set_tex_coord_index_listener_;
        exposedfield<sfnode> normal_;
        exposedfield<sfnode> tex_coord_;
        sfbool ccw_;
        sfbool convex_;
        sffloat crease_angle_;
        mfint32 normal_index_;
        sfbool normal_per_vertex_;
        sfbool solid_;
        mfint32 tex_coord_index_;

        bounding_sphere bsphere;

    public:
        indexed_face_set_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~indexed_face_set_node() throw ();

        virtual bool modified() const;

    private:
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;

        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);

        void recalc_bsphere();
    };


    class OPENVRML_LOCAL indexed_line_set_node :
        public abstract_indexed_set_node<indexed_line_set_node> {

        friend class indexed_line_set_class;

    public:
        indexed_line_set_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~indexed_line_set_node() throw ();

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
        virtual bool do_emissive() const throw ();
    };


    class OPENVRML_LOCAL inline_node : public abstract_node<inline_node>,
                                       public grouping_node {
        friend class inline_class;

        exposedfield<mfstring> url_;
        sfvec3f bbox_center_;
        sfvec3f bbox_size_;

        openvrml::scene * inlineScene;
        bool hasLoaded;

    public:
        inline_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~inline_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual const std::vector<boost::intrusive_ptr<node> > &
        do_children() const throw ();

        void load();
    };


    class OPENVRML_LOCAL lod_node : public abstract_node<lod_node>,
                                    public grouping_node {
        friend class lod_class;

        exposedfield<mfnode> level_;
        sfvec3f center_;
        mffloat range_;

        mfnode children_;
        bounding_sphere bsphere;

    public:
        lod_node(const node_type & type,
                 const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~lod_node() throw ();

        virtual bool modified() const;

    private:
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual const std::vector<boost::intrusive_ptr<node> > &
        do_children() const throw ();
        virtual void recalc_bsphere();
    };


    class OPENVRML_LOCAL material_node : public abstract_node<material_node>,
                                         public openvrml::material_node {
        friend class material_class;

        exposedfield<sffloat> ambient_intensity_;
        exposedfield<sfcolor> diffuse_color_;
        exposedfield<sfcolor> emissive_color_;
        exposedfield<sffloat> shininess_;
        exposedfield<sfcolor> specular_color_;
        exposedfield<sffloat> transparency_;

    public:
        material_node(const node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~material_node() throw ();

        //
        // material_node implementation
        //
        virtual float ambient_intensity() const throw ();
        virtual const color & diffuse_color() const throw ();
        virtual const color & emissive_color() const throw ();
        virtual float shininess() const throw ();
        virtual const color & specular_color() const throw ();
        virtual float transparency() const throw ();
    };


    class OPENVRML_LOCAL movie_texture_node :
        public abstract_texture_node<movie_texture_node>,
        public time_dependent_node {

        friend class movie_texture_class;

        class set_speed_listener : public event_listener_base<self_t>,
                                   public sffloat_listener {
        public:
            explicit set_speed_listener(movie_texture_node & node);
            virtual ~set_speed_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & speed,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        exposedfield<sfbool> loop_;
        set_speed_listener set_speed_;
        sffloat speed_;
        sffloat_emitter speed_changed_;
        exposedfield<sftime> start_time_;
        exposedfield<sftime> stop_time_;
        exposedfield<mfstring> url_;
        sftime duration_;
        sftime_emitter duration_changed_;
        sfbool active_;
        sfbool_emitter is_active_;

        openvrml::image image_;

    public:
        movie_texture_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~movie_texture_node() throw ();

        virtual const openvrml::image & image() const throw ();

    private:
        virtual void do_initialize(double timestamp) throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();
        virtual viewer::texture_object_t do_render_texture(viewer & v);
        virtual void do_update(double time);
    };


    class OPENVRML_LOCAL navigation_info_node :
        public abstract_node<navigation_info_node>,
        public openvrml::navigation_info_node {

        friend class navigation_info_class;

        class set_bind_listener : public event_listener_base<self_t>,
                                  public sfbool_listener {
        public:
            explicit set_bind_listener(navigation_info_node & node);
            virtual ~set_bind_listener() throw ();

        private:
            virtual void do_process_event(const sfbool & bind,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_bind_listener set_bind_listener_;
        exposedfield<mffloat> avatar_size_;
        exposedfield<sfbool> headlight_;
        exposedfield<sffloat> speed_;
        exposedfield<mfstring> type_;
        exposedfield<sffloat> visibility_limit_;
        sfbool is_bound_;
        sfbool_emitter is_bound_emitter_;

    public:
        navigation_info_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~navigation_info_node() throw ();

        virtual const std::vector<float> & avatar_size() const throw ();
        virtual bool headlight() const throw ();
        virtual float speed() const throw ();
        virtual const std::vector<std::string> & type() const throw ();
        virtual float visibility_limit() const throw ();

    private:
        virtual void do_initialize(double timestamp) throw ();
        virtual void do_shutdown(double timestamp) throw ();
    };


    class OPENVRML_LOCAL normal_node : public abstract_node<normal_node>,
                                       public openvrml::normal_node {
        friend class normal_class;

        exposedfield<mfvec3f> vector_;

    public:
        normal_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~normal_node() throw ();

        //
        // normal_node implementation.
        //
        virtual const std::vector<vec3f> & vector() const throw ();
    };


    class OPENVRML_LOCAL normal_interpolator_node :
        public abstract_node<normal_interpolator_node>,
        public child_node {

        friend class normal_interpolator_class;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(normal_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & fraction,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfvec3f> key_value_;
        mfvec3f value_changed_;
        mfvec3f_emitter value_changed_emitter_;

    public:
        normal_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~normal_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL orientation_interpolator_node :
        public abstract_node<orientation_interpolator_node>,
        public child_node {

        friend class orientation_interpolator_class;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(
                orientation_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & fraction,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfrotation> key_value_;
        sfrotation value_changed_;
        sfrotation_emitter value_changed_emitter_;

    public:
        orientation_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~orientation_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL pixel_texture_node :
        public abstract_texture_node<pixel_texture_node> {

        friend class pixel_texture_class;

        exposedfield<sfimage> image_;

    public:
        pixel_texture_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~pixel_texture_node() throw ();

        virtual const openvrml::image & image() const throw ();

    private:
        virtual viewer::texture_object_t do_render_texture(viewer & v);
    };


    class OPENVRML_LOCAL plane_sensor_node :
        public abstract_node<plane_sensor_node>,
        public pointing_device_sensor_node {

        friend class plane_sensor_class;

        exposedfield<sfbool> auto_offset_;
        exposedfield<sfbool> enabled_;
        exposedfield<sfvec2f> max_position_;
        exposedfield<sfvec2f> min_position_;
        exposedfield<sfvec3f> offset_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfvec3f track_point_changed_;
        sfvec3f_emitter track_point_changed_emitter_;
        sfvec3f translation_changed_;
        sfvec3f_emitter translation_changed_emitter_;

        sfvec3f activationPoint;

        mat4f activationMatrix;
        mat4f modelview;

    public:
        plane_sensor_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~plane_sensor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };


    class OPENVRML_LOCAL point_light_node :
        public abstract_light_node<point_light_node>,
        public scoped_light_node {

        friend class point_light_class;

        exposedfield<sfvec3f> attenuation_;
        exposedfield<sfvec3f> location_;
        exposedfield<sffloat> radius_;

    public:
        point_light_node(const node_type & type,
                         const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~point_light_node() throw ();

    private:
        virtual void do_initialize(double timestamp) throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();
        virtual void do_render_scoped_light(viewer & v);
    };


    class OPENVRML_LOCAL point_set_node : public abstract_node<point_set_node>,
                                          public geometry_node {

        friend class point_set_class;

        exposedfield<sfnode> color_;
        exposedfield<sfnode> coord_;

        bounding_sphere bsphere;

    public:
        point_set_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~point_set_node() throw ();

        virtual bool modified() const;

    private:
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;

        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
        virtual bool do_emissive() const throw ();

        void recalc_bsphere();
    };


    class OPENVRML_LOCAL position_interpolator_node :
        public abstract_node<position_interpolator_node>,
        public child_node {

        friend class position_interpolator_class;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(position_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & fraction,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mfvec3f> key_value_;
        sfvec3f value_changed_;
        sfvec3f_emitter value_changed_emitter_;

    public:
        position_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~position_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL proximity_sensor_node :
        public abstract_node<proximity_sensor_node>,
        public child_node {

        friend class proximity_sensor_class;

        exposedfield<sfvec3f> center_;
        exposedfield<sfbool> enabled_;
        exposedfield<sfvec3f> size_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfvec3f position_changed_;
        sfvec3f_emitter position_changed_emitter_;
        sfrotation orientation_changed_;
        sfrotation_emitter orientation_changed_emitter_;
        sftime enter_time_;
        sftime_emitter enter_time_emitter_;
        sftime exit_time_;
        sftime_emitter exit_time_emitter_;

    public:
        proximity_sensor_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~proximity_sensor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL scalar_interpolator_node :
        public abstract_node<scalar_interpolator_node>,
        public child_node {

        friend class scalar_interpolator_class;

        class set_fraction_listener : public event_listener_base<self_t>,
                                      public sffloat_listener {
        public:
            explicit set_fraction_listener(scalar_interpolator_node & node);
            virtual ~set_fraction_listener() throw ();

        private:
            virtual void do_process_event(const sffloat & fraction,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_fraction_listener set_fraction_listener_;
        exposedfield<mffloat> key_;
        exposedfield<mffloat> key_value_;
        sffloat value_changed_;
        sffloat_emitter value_changed_emitter_;

    public:
        scalar_interpolator_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~scalar_interpolator_node() throw ();
    };


    class OPENVRML_LOCAL shape_node : public abstract_node<shape_node>,
                                      public child_node {
        friend class shape_class;

        exposedfield<sfnode> appearance_;
        exposedfield<sfnode> geometry_;

        viewer::object_t viewerObject;

    public:
        shape_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~shape_node() throw ();

        virtual bool modified() const;

    private:
        virtual const openvrml::bounding_volume & do_bounding_volume() const;

        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL sound_node : public abstract_node<sound_node>,
                                      public child_node {
        friend class sound_class;

        exposedfield<sfvec3f> direction_;
        exposedfield<sffloat> intensity_;
        exposedfield<sfvec3f> location_;
        exposedfield<sffloat> max_back_;
        exposedfield<sffloat> max_front_;
        exposedfield<sffloat> min_back_;
        exposedfield<sffloat> min_front_;
        exposedfield<sffloat> priority_;
        exposedfield<sfnode> source_;
        sfbool spatialize_;

    public:
        sound_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~sound_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL sphere_node : public abstract_node<sphere_node>,
                                       public geometry_node {
        friend class sphere_class;

        sffloat radius;
        bounding_sphere bsphere;

    public:
        sphere_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~sphere_node() throw ();

    private:
        virtual const openvrml::bounding_volume & do_bounding_volume() const;
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);
    };


    class OPENVRML_LOCAL sphere_sensor_node :
        public abstract_node<sphere_sensor_node>,
        public pointing_device_sensor_node {

        friend class sphere_sensor_class;

        exposedfield<sfbool> auto_offset_;
        exposedfield<sfbool> enabled_;
        exposedfield<sfrotation> offset_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfrotation rotation_changed_;
        sfrotation_emitter rotation_changed_emitter_;
        sfvec3f track_point_changed_;
        sfvec3f_emitter track_point_changed_emitter_;

        sfvec3f activationPoint;
        sfvec3f centerPoint;
        mat4f modelview;

    public:
        sphere_sensor_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~sphere_sensor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };


    class OPENVRML_LOCAL spot_light_node :
        public abstract_light_node<spot_light_node>,
        public scoped_light_node {

        friend class spot_light_class;

        exposedfield<sfvec3f> attenuation_;
        exposedfield<sffloat> beam_width_;
        exposedfield<sffloat> cut_off_angle_;
        exposedfield<sfvec3f> direction_;
        exposedfield<sfvec3f> location_;
        exposedfield<sffloat> radius_;

    public:
        spot_light_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~spot_light_node() throw ();

    private:
        virtual void do_initialize(double timestamp)
            throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();
        virtual void do_render_scoped_light(viewer & v);
    };


    class OPENVRML_LOCAL switch_node : public abstract_node<switch_node>,
                                       public grouping_node {
        friend class switch_class;

        class choice_exposedfield : public exposedfield<mfnode> {
        public:
            explicit choice_exposedfield(switch_node & node);
            choice_exposedfield(const choice_exposedfield & obj) throw ();
            virtual ~choice_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfnode & choice,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class which_choice_exposedfield : public exposedfield<sfint32> {
        public:
            explicit which_choice_exposedfield(switch_node & node);
            which_choice_exposedfield(const which_choice_exposedfield & obj)
                throw ();
            virtual ~which_choice_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfint32 & which_choice,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        choice_exposedfield choice_;
        which_choice_exposedfield which_choice_;

        mfnode children_;
        bounding_sphere bsphere;

    public:
        switch_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~switch_node() throw ();

        virtual bool modified() const;

    private:
        virtual const openvrml::bounding_volume & do_bounding_volume() const;
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
        virtual const std::vector<boost::intrusive_ptr<node> > &
        do_children() const throw ();
        virtual void recalc_bsphere();
    };


    class OPENVRML_LOCAL text_node : public abstract_node<text_node>,
                                     public geometry_node {
        friend class text_class;

        class string_exposedfield : public exposedfield<mfstring> {
        public:
            explicit string_exposedfield(text_node & node);
            string_exposedfield(const string_exposedfield & obj) throw ();
            virtual ~string_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mfstring & string,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class font_style_exposedfield : public exposedfield<sfnode> {
        public:
            explicit font_style_exposedfield(text_node & node);
            font_style_exposedfield(const font_style_exposedfield & obj)
                throw ();
            virtual ~font_style_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfnode & font_style,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class length_exposedfield : public exposedfield<mffloat> {
        public:
            explicit length_exposedfield(text_node & node);
            length_exposedfield(const length_exposedfield & obj) throw ();
            virtual ~length_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const mffloat & length,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class max_extent_exposedfield : public exposedfield<sffloat> {
        public:
            explicit max_extent_exposedfield(text_node & node);
            max_extent_exposedfield(const max_extent_exposedfield & obj)
                throw ();
            virtual ~max_extent_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sffloat & max_extent,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        string_exposedfield string_;
        font_style_exposedfield font_style_;
        length_exposedfield length_;
        max_extent_exposedfield max_extent_;

        struct glyph_geometry {
            std::vector<vec2f> coord;
            std::vector<int32> coord_index;
            float advance_width;
            float advance_height;

            glyph_geometry(const std::vector<std::vector<vec2f> > & contours,
                           float advance_width,
                           float advance_height)
                throw (std::bad_alloc);
        };

        struct text_geometry {
            std::vector<vec3f> coord;
            std::vector<int32> coord_index;
            std::vector<vec3f> normal;
            std::vector<vec2f> tex_coord;
        };

# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        typedef std::vector<std::vector<FcChar32> > ucs4_string_t;
        typedef std::map<FT_UInt, glyph_geometry> glyph_geometry_map_t;

        ucs4_string_t ucs4_string;
        FT_Face face;
        glyph_geometry_map_t glyph_geometry_map;
# endif
        text_geometry text_geometry_;

    public:
        text_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~text_node() throw ();

        virtual bool modified() const;

    private:
        virtual viewer::object_t do_render_geometry(openvrml::viewer & viewer,
                                                    rendering_context context);

        virtual void do_initialize(double timestamp)
            throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();

        void update_ucs4() throw (std::bad_alloc);
        void update_face() throw (std::bad_alloc);
        void update_geometry() throw (std::bad_alloc);
    };


    class OPENVRML_LOCAL texture_coordinate_node :
        public abstract_node<texture_coordinate_node>,
        public openvrml::texture_coordinate_node {

        friend class texture_coordinate_class;

        exposedfield<mfvec2f> point_;

    public:
        texture_coordinate_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~texture_coordinate_node() throw ();

        //
        // texture_coordinate_node implementation.
        //
        virtual const std::vector<vec2f> & point() const throw();
    };


    class OPENVRML_LOCAL texture_transform_node :
        public abstract_node<texture_transform_node>,
        public openvrml::texture_transform_node {

        friend class texture_transform_class;

        exposedfield<sfvec2f> center_;
        exposedfield<sffloat> rotation_;
        exposedfield<sfvec2f> scale_;
        exposedfield<sfvec2f> translation_;

    public:
        texture_transform_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~texture_transform_node() throw ();

    private:
        virtual void do_render_texture_transform(viewer & v);
    };


    class OPENVRML_LOCAL time_sensor_node :
        public abstract_node<time_sensor_node>,
        public time_dependent_node,
        public child_node {

        friend class time_sensor_class;

        class set_cycle_interval_listener : public event_listener_base<self_t>,
                                            public sftime_listener {
        public:
            explicit set_cycle_interval_listener(time_sensor_node & node);
            virtual ~set_cycle_interval_listener() throw ();

        private:
            virtual void do_process_event(const sftime & cycle_interval,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class enabled_exposedfield : public exposedfield<sfbool> {
        public:
            explicit enabled_exposedfield(time_sensor_node & node);
            enabled_exposedfield(const enabled_exposedfield & obj) throw ();
            virtual ~enabled_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfbool & enabled,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class set_start_time_listener : public event_listener_base<self_t>,
                                        public sftime_listener {
        public:
            explicit set_start_time_listener(time_sensor_node & node);
            virtual ~set_start_time_listener() throw ();

        private:
            virtual void do_process_event(const sftime & start_time,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        set_cycle_interval_listener set_cycle_interval_listener_;
        sftime cycle_interval_;
        sftime_emitter cycle_interval_changed_emitter_;
        enabled_exposedfield enabled_;
        exposedfield<sfbool> loop_;
        set_start_time_listener set_start_time_listener_;
        sftime start_time_;
        sftime_emitter start_time_changed_emitter_;
        exposedfield<sftime> stop_time_;
        sftime cycle_time_;
        sftime_emitter cycle_time_emitter_;
        sffloat fraction_changed_;
        sffloat_emitter fraction_changed_emitter_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sftime time_;
        sftime_emitter time_emitter_;

        double lastTime;

    public:
        time_sensor_node(const node_type & type,
                         const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~time_sensor_node() throw ();

    private:
        virtual void do_initialize(double timestamp)
            throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();
        virtual void do_update(double time);
    };


    class OPENVRML_LOCAL touch_sensor_node :
        public abstract_node<touch_sensor_node>,
        public pointing_device_sensor_node {

        friend class touch_sensor_class;

        exposedfield<sfbool> enabled_;
        sfvec3f hit_normal_changed_;
        sfvec3f_emitter hit_normal_changed_emitter_;
        sfvec3f hit_point_changed_;
        sfvec3f_emitter hit_point_changed_emitter_;
        sfvec2f hit_tex_coord_changed_;
        sfvec2f_emitter hit_tex_coord_changed_emitter_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sfbool is_over_;
        sfbool_emitter is_over_emitter_;
        sftime touch_time_;
        sftime_emitter touch_time_emitter_;

    public:
        touch_sensor_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~touch_sensor_node() throw ();

    private:
        virtual void do_activate(double timestamp, bool over, bool active,
                                 const double (&point)[3]);
    };


    class OPENVRML_LOCAL transform_node :
        public grouping_node_base<transform_node>,
        public openvrml::transform_node {

        friend class transform_class;

        class center_exposedfield : public exposedfield<sfvec3f> {
        public:
            explicit center_exposedfield(transform_node & node);
            center_exposedfield(const center_exposedfield & obj) throw ();
            virtual ~center_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfvec3f & center,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class rotation_exposedfield : public exposedfield<sfrotation> {
        public:
            explicit rotation_exposedfield(transform_node & node);
            rotation_exposedfield(const rotation_exposedfield & obj) throw ();
            virtual ~rotation_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfrotation & rotation,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class scale_exposedfield : public exposedfield<sfvec3f> {
        public:
            explicit scale_exposedfield(transform_node & node);
            scale_exposedfield(const scale_exposedfield & obj) throw ();
            virtual ~scale_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfvec3f & scale,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class scale_orientation_exposedfield :
            public exposedfield<sfrotation> {
        public:
            explicit scale_orientation_exposedfield(transform_node & node);
            scale_orientation_exposedfield(
                const scale_orientation_exposedfield & obj) throw ();
            virtual ~scale_orientation_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void
            event_side_effect(const sfrotation & scale_orientation,
                              double timestamp)
                throw (std::bad_alloc);
        };

        class translation_exposedfield : public exposedfield<sfvec3f> {
        public:
            explicit translation_exposedfield(transform_node & node);
            translation_exposedfield(const translation_exposedfield & obj)
                throw ();
            virtual ~translation_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfvec3f & translation,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        center_exposedfield center_;
        rotation_exposedfield rotation_;
        scale_exposedfield scale_;
        scale_orientation_exposedfield scale_orientation_;
        translation_exposedfield translation_;

        mutable mat4f transform_;
        mutable bool transform_dirty;
        viewer::object_t xformObject;

    public:
        transform_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~transform_node() throw ();

        virtual const mat4f & transform() const throw ();

    private:
        virtual const openvrml::bounding_volume &
        do_bounding_volume() const;

        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);

        void recalc_bsphere();
        void update_transform() const throw ();
    };


    class OPENVRML_LOCAL viewpoint_node :
        public abstract_node<viewpoint_node>,
        public openvrml::viewpoint_node {

        friend class viewpoint_class;

        class set_bind_listener : public event_listener_base<self_t>,
                                  public sfbool_listener {
        public:
            explicit set_bind_listener(viewpoint_node & node);
            virtual ~set_bind_listener() throw ();

        private:
            virtual void do_process_event(const sfbool & value,
                                          double timestamp)
                throw (std::bad_alloc);
        };

        class orientation_exposedfield : public exposedfield<sfrotation> {
        public:
            explicit orientation_exposedfield(viewpoint_node & node);
            orientation_exposedfield(const orientation_exposedfield & obj)
                throw ();
            virtual ~orientation_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfrotation & orientation,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        class position_exposedfield : public exposedfield<sfvec3f> {
        public:
            explicit position_exposedfield(viewpoint_node & node);
            position_exposedfield(const position_exposedfield & obj) throw ();
            virtual ~position_exposedfield() throw ();

        private:
            virtual std::auto_ptr<field_value> do_clone() const
                throw (std::bad_alloc);
            virtual void event_side_effect(const sfvec3f & position,
                                           double timestamp)
                throw (std::bad_alloc);
        };

        set_bind_listener set_bind_listener_;
        exposedfield<sffloat> field_of_view_;
        exposedfield<sfbool> jump_;
        orientation_exposedfield orientation_;
        position_exposedfield position_;
        sfstring description_;
        sfbool is_bound_;
        sfbool_emitter is_bound_emitter_;
        sftime bind_time_;
        sftime_emitter bind_time_emitter_;

        mat4f parent_transform;
        mutable mat4f final_transformation;
        mutable bool final_transformation_dirty;
        mat4f user_view_transform_;

    public:
        viewpoint_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~viewpoint_node() throw ();

        virtual const mat4f & transformation() const throw ();
        virtual const mat4f & user_view_transform() const throw ();
        virtual void user_view_transform(const mat4f & transform) throw ();
        virtual const std::string & description() const throw ();
        virtual float field_of_view() const throw ();

        const sfrotation & orientation() const;
        const sfvec3f & position() const;

    private:
        virtual void do_initialize(double timestamp) throw ();
        virtual void do_relocate() throw (std::bad_alloc);
        virtual void do_shutdown(double timestamp) throw ();

        void update_final_transformation() const throw ();
    };


    class OPENVRML_LOCAL visibility_sensor_node :
        public abstract_node<visibility_sensor_node>,
        public child_node {

        friend class visibility_sensor_class;

        exposedfield<sfvec3f> center_;
        exposedfield<sfbool> enabled_;
        exposedfield<sfvec3f> size_;
        sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        sftime enter_time_;
        sftime_emitter enter_time_emitter_;
        sftime exit_time_;
        sftime_emitter exit_time_emitter_;

    public:
        visibility_sensor_node(
            const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~visibility_sensor_node() throw ();

    private:
        virtual void do_render_child(openvrml::viewer & viewer,
                                     rendering_context context);
    };


    class OPENVRML_LOCAL world_info_node :
        public abstract_node<world_info_node>,
        public child_node {

        friend class world_info_class;

        mfstring info;
        sfstring title;

    public:
        world_info_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~world_info_node() throw ();
    };


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this anchor_class.
     */
    anchor_class::anchor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    anchor_class::~anchor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a node_type_ptr to a node_type capable of creating Anchor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by anchor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    anchor_class::do_create_type(const std::string & id,
                                 const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "addChildren"),
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "removeChildren"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "children"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfstring_id,
                           "description"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "parameter"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "url"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize")
        };

        typedef node_type_impl<anchor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & anchorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                anchorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        anchor_node::add_children_listener>(
                            &anchor_node::add_children_listener_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        anchor_node::remove_children_listener>(
                            &anchor_node::remove_children_listener_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        anchor_node::children_exposedfield>(
                            &anchor_node::children_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        anchor_node::children_exposedfield>(
                            &anchor_node::children_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        anchor_node::children_exposedfield>(
                            &anchor_node::children_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<anchor_node>::exposedfield<sfstring> >(
                            &anchor_node::description_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<anchor_node>::exposedfield<sfstring> >(
                            &anchor_node::description_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<anchor_node>::exposedfield<sfstring> >(
                            &anchor_node::description_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::parameter_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::parameter_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::parameter_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<anchor_node>::exposedfield<mfstring> >(
                            &anchor_node::url_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &anchor_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                anchorNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &anchor_node::bbox_size_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class anchor_node
     *
     * @brief Represents Anchor node instances.
     */

    /**
     * @var anchor_node::anchor_class
     *
     * @brief Class object for Anchor nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<anchor_node>::exposedfield<openvrml::sfstring> anchor_node::description_
     *
     * @brief description exposedField
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<anchor_node>::exposedfield<openvrml::mfstring> anchor_node::parameter_
     *
     * @brief parameter exposedField
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<anchor_node>::exposedfield<openvrml::mfstring> anchor_node::url_
     *
     * @brief url exposedField
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope     the scope to which the node belongs.
     */
    anchor_node::
    anchor_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        grouping_node_base<anchor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        description_(*this),
        parameter_(*this),
        url_(*this)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    anchor_node::~anchor_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    anchor_node::
    do_render_child(openvrml::viewer & viewer, const rendering_context context)
    {
        viewer.set_sensitive(this);

        // Render children
        this->grouping_node_base<anchor_node>::do_render_child(viewer,
                                                               context);

        viewer.set_sensitive(0);
    }

    /**
     * @brief Handle a click by loading the url.
     */
    void anchor_node::do_activate(double,
                                  const bool over,
                                  const bool active,
                                  const double (&)[3])
    {
        assert(this->scene());
        //
        // @todo This should really be (is_over && !is_active && n->was_active)
        // (ie, button up over the anchor after button down over the
        // anchor)
        //
        if (over && active) {
            this->scene()->load_url(this->url_.mfstring::value(),
                                    this->parameter_.mfstring::value());
        }
    }

    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    appearance_class::
    appearance_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    appearance_class::~appearance_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Appearance nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by appearance_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    appearance_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 3> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "material"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "texture"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "textureTransform")
        };

        typedef node_type_impl<appearance_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & appearanceNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                appearanceNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::material_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::material_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::material_)));
            } else if (*interface == *++supported_interface) {
                appearanceNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_)));
            } else if (*interface == *++supported_interface) {
                appearanceNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_transform_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_transform_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<appearance_node>::exposedfield<sfnode> >(
                            &appearance_node::texture_transform_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class appearance_node
     *
     * @brief Appearance node instances.
     */

    /**
     * @var appearance_node::appearance_class
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
    appearance_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<appearance_node>(type, scope),
        openvrml::appearance_node(type, scope),
        material_(*this),
        texture_(*this),
        texture_transform_(*this)
    {}

    /**
     * @brief Destroy.
     */
    appearance_node::~appearance_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *         @c false otherwise.
     */
    bool appearance_node::modified() const
    {
        return (this->node::modified()
                || (this->material_.sfnode::value()
                    && this->material_.sfnode::value()->modified())
                || (this->texture_.sfnode::value()
                    && this->texture_.sfnode::value()->modified())
                || (this->texture_transform_.sfnode::value()
                    && this->texture_transform_.sfnode::value()->modified()));
    }

    /**
     * @brief Get the material node.
     *
     * @returns an sfnode object containing the Material node associated with
     *          this Appearance.
     */
    const boost::intrusive_ptr<openvrml::node> &
    appearance_node::material() const throw ()
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
    appearance_node::texture() const throw ()
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
    appearance_node::texture_transform() const throw ()
    {
        return this->texture_transform_.sfnode::value();
    }

    OPENVRML_LOCAL void set_unlit_material(openvrml::viewer & v)
    {
        using openvrml::color;
        static const float unlit_ambient_intensity(1);
        static const color unlit_diffuse_color(1, 1, 1);
        static const color unlit_emissive_color(1, 1, 1);
        static const float unlit_shininess(0);
        static const color unlit_specular_color(1, 1, 1);
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
    do_render_appearance(viewer & v, rendering_context)
    {
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
            if (nTexComponents >= 3) { diffuse = color(1.0, 1.0, 1.0); }

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
                static const vec2f center(0.0, 0.0);
                static const float rotation = 0.0;
                static const vec2f scale(1.0, 1.0);
                static const vec2f translation(0.0, 0.0);
                v.set_texture_transform(center, rotation, scale, translation);
            }
            texture->render_texture(v);
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    audio_clip_class::
    audio_clip_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    audio_clip_class::~audio_clip_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating AudioClip nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by audio_clip_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    audio_clip_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfstring_id,
                           "description"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "loop"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "pitch"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "startTime"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "stopTime"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "url"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "duration_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive")
        };

        typedef node_type_impl<audio_clip_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & audioClipNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfstring> >(
                            &audio_clip_node::description_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfstring> >(
                            &audio_clip_node::description_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfstring> >(
                            &audio_clip_node::description_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfbool> >(
                            &audio_clip_node::loop_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfbool> >(
                            &audio_clip_node::loop_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sfbool> >(
                            &audio_clip_node::loop_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sffloat> >(
                            &audio_clip_node::pitch_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sffloat> >(
                            &audio_clip_node::pitch_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sffloat> >(
                            &audio_clip_node::pitch_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::start_time_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::start_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::start_time_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::stop_time_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::stop_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<sftime> >(
                            &audio_clip_node::stop_time_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<audio_clip_node>::exposedfield<mfstring> >(
                            &audio_clip_node::url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<audio_clip_node>::exposedfield<mfstring> >(
                            &audio_clip_node::url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::exposedfield<mfstring> >(
                            &audio_clip_node::url_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::sftime_emitter>(
                            &audio_clip_node::duration_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                audioClipNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<audio_clip_node>::sfbool_emitter>(
                            &audio_clip_node::is_active_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class audio_clip_node
     *
     * @brief AudioClip node instances.
     *
     * @todo Implement sound support.
     */

    /**
     * @var audio_clip_node::audio_clip_class
     *
     * @brief Class object for AudioClip nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sfstring> audio_clip_node::description_
     *
     * @brief description exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sfbool> audio_clip_node::loop_
     *
     * @brief loop exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sffloat> audio_clip_node::pitch_
     *
     * @brief pitch exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sftime> audio_clip_node::start_time_
     *
     * @brief startTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sftime> audio_clip_node::stop_time_
     *
     * @brief stopTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::mfstring> audio_clip_node::url_
     *
     * @brief url exposedField.
     */

    /**
     * @var openvrml::sftime audio_clip_node::duration_changed_
     *
     * @brief duration_changed eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter audio_clip_node::duration_changed_emitter_
     *
     * @brief duration_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfbool audio_clip_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter audio_clip_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type      the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    audio_clip_node::
    audio_clip_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<audio_clip_node>(type, scope),
        time_dependent_node(type, scope),
        description_(*this),
        loop_(*this),
        pitch_(*this, 1.0),
        start_time_(*this),
        stop_time_(*this),
        url_(*this),
        duration_changed_emitter_(*this, this->duration_changed_),
        is_active_emitter_(*this, this->is_active_)
    {}

    /**
     * @brief Destroy.
     */
    audio_clip_node::~audio_clip_node() throw ()
    {}

    /**
     * @brief Called to update the AudioClip for the current time.
     *
     * @param time  the current time.
     *
     * @todo Implement me!
     */
    void audio_clip_node::do_update(double)
    {}

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    audio_clip_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_time_dependent(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    audio_clip_node::do_shutdown(double) throw ()
    {
        assert(this->scene());
        this->scene()->browser().remove_time_dependent(*this);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    background_class::
    background_class(openvrml::browser & browser):
        node_class(browser),
        first(0)
    {}

    /**
     * @brief Destroy.
     */
    background_class::~background_class() throw ()
    {}

    /**
     * @brief Set the first Background node in the world.
     *
     * The first Background node in the world is used as the initial
     * background. This method is used by
     * <code>background_node::do_initialize</code>.
     *
     * @param background    a Background node.
     */
    void
    background_class::
    set_first(background_node & background) throw ()
    {
        this->first = &background;
    }

    /**
     * @brief Reset the pointer to the first Background node in the world to
     *        null.
     *
     * This function is called by <code>background_node::do_shutdown</code>.
     */
    void background_class::reset_first() throw ()
    {
        this->first = 0;
    }

    /**
     * @brief Check to see if the first node has been set.
     *
     * This method is used by background_node::do_initialize.
     *
     * @return @c true if the first node has already been set; @c false
     *         otherwise.
     */
    bool background_class::has_first() const throw ()
    {
        return this->first;
    }

    /**
     * @brief Check to see if a node is registered as the "first" node.
     *
     * @param background    a background_node.
     *
     * @return @c true if @p background is the fist node; @c false otherwise.
     */
    bool
    background_class::is_first(background_node & background)
        throw ()
    {
        return &background == this->first;
    }

    /**
     * @brief Push a background_node on the top of the bound node stack.
     *
     * @param background    the node to bind.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_class::bind(background_node & background,
                           const double timestamp)
        throw (std::bad_alloc)
    {
        using std::find;

        //
        // If the node is already the active node, do nothing.
        //
        if (!this->bound_nodes.empty()
            && &background == this->bound_nodes.back()) {
            return;
        }

        //
        // If the node is already on the stack, remove it.
        //
        const bound_nodes_t::iterator pos = find(this->bound_nodes.begin(),
                                                 this->bound_nodes.end(),
                                                 &background);
        if (pos != this->bound_nodes.end()) { this->bound_nodes.erase(pos); }

        //
        // Send FALSE from the currently active node's isBound.
        //
        if (!this->bound_nodes.empty()) {
            background_node & current =
                dynamic_cast<background_node &>(*this->bound_nodes.back());
            current.is_bound_.value(false);
            node::emit_event(current.is_bound_emitter_, timestamp);
        }

        //
        // Push the node to the top of the stack, and have it send isBound
        // TRUE.
        //
        this->bound_nodes.push_back(&background);
        background.is_bound_.value(true);
        node::emit_event(background.is_bound_emitter_, timestamp);
    }

    /**
     * @brief Remove a background_node from the bound node stack.
     *
     * @param background    the node to unbind.
     * @param timestamp     the current time.
     */
    void
    background_class::unbind(background_node & background,
                             const double timestamp)
        throw ()
    {
        using std::find;

        const bound_nodes_t::iterator pos = find(this->bound_nodes.begin(),
                                                 this->bound_nodes.end(),
                                                 &background);
        if (pos != this->bound_nodes.end()) {
            background.is_bound_.value(false);
            node::emit_event(background.is_bound_emitter_, timestamp);

            if (pos == this->bound_nodes.end() - 1
                && this->bound_nodes.size() > 1) {
                background_node & newActive =
                    dynamic_cast<background_node &>(
                        **(this->bound_nodes.end() - 2));
                newActive.is_bound_.value(true);
                node::emit_event(newActive.is_bound_emitter_, timestamp);
            }
            this->bound_nodes.erase(pos);
        }
    }

    /**
     * @brief node_class-specific initialization.
     *
     * @param initial_viewpoint the viewpoint_node that should be bound
     *                          initially.
     * @param timestamp         the current time.
     */
    void
    background_class::
    do_initialize(openvrml::viewpoint_node *, const double timestamp) throw ()
    {
        if (this->first) {
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

    /**
     * @brief node_class-specific rendering.
     *
     * Render the active Background node.
     *
     * @param v viewer.
     */
    void background_class::do_render(viewer & v) const
        throw ()
    {
        if (this->bound_nodes.empty()) {
            //
            // Default background.
            //
            using std::vector;
            static const vector<float> ground_angle;
            static const vector<color> ground_color;
            static const vector<float> sky_angle;
            static const vector<color> sky_color;
            static const image front;
            static const image back;
            static const image left;
            static const image right;
            static const image top;
            static const image bottom;
            v.insert_background(ground_angle,
                                ground_color,
                                sky_angle,
                                sky_color,
                                front,
                                back,
                                left,
                                right,
                                top,
                                bottom);
        } else {
            assert(this->bound_nodes.back());
            background_node & background = *this->bound_nodes.back();

            // Background isn't selectable, so don't waste the time.
            if (v.mode() == viewer::pick_mode) { return; }

            if (background.viewerObject && background.modified()) {
                v.remove_object(background.viewerObject);
                background.viewerObject = 0;
            }

            if (background.viewerObject) {
                v.insert_reference(background.viewerObject);
            } else {
                background.update_textures();

                background.viewerObject =
                    v.insert_background(
                        background.ground_angle_.mffloat::value(),
                        background.ground_color_.mfcolor::value(),
                        background.sky_angle_.mffloat::value(),
                        background.sky_color_.mfcolor::value(),
                        background.front,
                        background.back,
                        background.left,
                        background.right,
                        background.top,
                        background.bottom);

                background.modified(false);
            }
        }
    }

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Background nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by background_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    background_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 12> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sfbool_id,
                           "set_bind"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "groundAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfcolor_id,
                           "groundColor"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "backUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "bottomUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "frontUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "leftUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "rightUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "topUrl"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "skyAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfcolor_id,
                           "skyColor"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isBound")
        };

        typedef node_type_impl<background_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & backgroundNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                backgroundNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::set_bind_listener>(
                            &background_node::set_bind_listener_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::ground_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::ground_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::ground_angle_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::ground_color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::ground_color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::ground_color_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::back_url_exposedfield>(
                            &background_node::back_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::back_url_exposedfield>(
                            &background_node::back_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::back_url_exposedfield>(
                            &background_node::back_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::bottom_url_exposedfield>(
                            &background_node::bottom_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::bottom_url_exposedfield>(
                            &background_node::bottom_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::bottom_url_exposedfield>(
                            &background_node::bottom_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::front_url_exposedfield>(
                            &background_node::front_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::front_url_exposedfield>(
                            &background_node::front_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::front_url_exposedfield>(
                            &background_node::front_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::left_url_exposedfield>(
                            &background_node::left_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::left_url_exposedfield>(
                            &background_node::left_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::left_url_exposedfield>(
                            &background_node::left_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::right_url_exposedfield>(
                            &background_node::right_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::right_url_exposedfield>(
                            &background_node::right_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::right_url_exposedfield>(
                            &background_node::right_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        background_node::top_url_exposedfield>(
                            &background_node::top_url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        background_node::top_url_exposedfield>(
                            &background_node::top_url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        background_node::top_url_exposedfield>(
                            &background_node::top_url_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::sky_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::sky_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<background_node>::exposedfield<mffloat> >(
                            &background_node::sky_angle_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::sky_color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::sky_color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<background_node>::exposedfield<mfcolor> >(
                            &background_node::sky_color_)));
            } else if (*interface == *++supported_interface) {
                backgroundNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<background_node>::sfbool_emitter>(
                            &background_node::is_bound_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class background_node
     *
     * @brief Background node instances.
     */

    /**
     * @var background_node::background_class
     *
     * @brief Class object for Background nodes.
     */

    /**
     * @internal
     *
     * @class background_node::set_bind_listener
     *
     * @brief set_bind eventIn listener.
     */

    /**
     * @brief Construct.
     *
     * @param node background_node.
     */
    background_node::set_bind_listener::
    set_bind_listener(background_node & node):
        node_event_listener(node),
        event_listener_base<background_node>(node),
        sfbool_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    background_node::set_bind_listener::~set_bind_listener()
        throw ()
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
    background_node::set_bind_listener::
    do_process_event(const sfbool & value, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            background_node & node =
                dynamic_cast<background_node &>(this->node());
            background_class & node_class =
                const_cast<background_class &>(
                    static_cast<const background_class &>(
                        node.type().node_class()));
            if (value.value()) {
                node_class.bind(node, timestamp);
            } else {
                node_class.unbind(node, timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::back_url_exposedfield
     *
     * @brief backUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::back_url_exposedfield::
    back_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<openvrml::mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::back_url_exposedfield::
    back_url_exposedfield(const back_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::back_url_exposedfield::
    ~back_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::back_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new back_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new backUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::back_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .back_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::bottom_url_exposedfield
     *
     * @brief bottomUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::bottom_url_exposedfield::
    bottom_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::bottom_url_exposedfield::
    bottom_url_exposedfield(const bottom_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::bottom_url_exposedfield::
    ~bottom_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::bottom_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new bottom_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new bottomUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::bottom_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .bottom_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::front_url_exposedfield
     *
     * @brief frontUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::front_url_exposedfield::
    front_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::front_url_exposedfield::
    front_url_exposedfield(const front_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::front_url_exposedfield::
    ~front_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::front_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new front_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new frontUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::front_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .front_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::left_url_exposedfield
     *
     * @brief leftUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::left_url_exposedfield::
    left_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::left_url_exposedfield::
    left_url_exposedfield(const left_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::left_url_exposedfield::
    ~left_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::left_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new left_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new leftUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::left_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .left_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::right_url_exposedfield
     *
     * @brief rightUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::right_url_exposedfield::
    right_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::right_url_exposedfield::
    right_url_exposedfield(const right_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::right_url_exposedfield::
    ~right_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::right_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new right_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new rightUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::right_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .right_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class background_node::top_url_exposedfield
     *
     * @brief topUrl exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  background_node.
     */
    background_node::top_url_exposedfield::
    top_url_exposedfield(background_node & node) throw ():
        node_event_listener(node),
        event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    background_node::top_url_exposedfield::
    top_url_exposedfield(const top_url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    background_node::top_url_exposedfield::
    ~top_url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    background_node::top_url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new top_url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param value     new topUrl value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    background_node::top_url_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            dynamic_cast<background_node &>(this->node_event_listener::node())
                .top_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var background_node::set_bind_listener background_node::set_bind_listener_
     *
     * @brief set_bind eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<background_node>::exposedfield<openvrml::mffloat> background_node::ground_angle_
     *
     * @brief groundAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<background_node>::exposedfield<openvrml::mfcolor> background_node::ground_color_
     *
     * @brief groundColor exposedField.
     */

    /**
     * @var background_node::back_url_exposedfield background_node::back_url_
     *
     * @brief backUrl exposedField.
     */

    /**
     * @var background_node::bottom_url_exposedfield background_node::bottom_url_
     *
     * @brief bottomUrl exposedField.
     */

    /**
     * @var background_node::front_url_exposedfield background_node::front_url_
     *
     * @brief frontUrl exposedField.
     */

    /**
     * @var background_node::left_url_exposedfield background_node::left_url_
     *
     * @brief leftUrl exposedField.
     */

    /**
     * @var background_node::right_url_exposedfield background_node::right_url_
     *
     * @brief rightUrl exposedField.
     */

    /**
     * @var background_node::top_url_exposedfield background_node::top_url_
     *
     * @brief topUrl exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<background_node>::exposedfield<openvrml::mffloat> background_node::sky_angle_
     *
     * @brief skyAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<background_node>::exposedfield<openvrml::mfcolor> background_node::sky_color_
     *
     * @brief skyColor exposedField.
     */

    /**
     * @var openvrml::sfbool background_node::is_bound_
     *
     * @brief isBound eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter background_node::is_bound_emitter_
     *
     * @brief isBound eventOut emitter.
     */

    /**
     * @var openvrml::image background_node::front
     *
     * @brief Front image.
     */

    /**
     * @var bool background_node::front_needs_update
     *
     * @brief Flag to indicate that the front image needs to be updated.
     */

    /**
     * @var openvrml::image background_node::back
     *
     * @brief Back image.
     */

    /**
     * @var bool background_node::back_needs_update
     *
     * @brief Flag to indicate that the back image needs to be updated.
     */

    /**
     * @var openvrml::image background_node::left
     *
     * @brief Left image.
     */

    /**
     * @var bool background_node::left_needs_update
     *
     * @brief Flag to indicate that the left image needs to be updated.
     */

    /**
     * @var openvrml::image background_node::right
     *
     * @brief Right image.
     */

    /**
     * @var bool background_node::right_needs_update
     *
     * @brief Flag to indicate that the right image needs to be updated.
     */

    /**
     * @var openvrml::image background_node::top
     *
     * @brief Top image.
     */

    /**
     * @var bool background_node::top_needs_update
     *
     * @brief Flag to indicate that the top image needs to be updated.
     */

    /**
     * @var openvrml::image background_node::bottom
     *
     * @brief Bottom image.
     */

    /**
     * @var bool background_node::bottom_needs_update
     *
     * @brief Flag to indicate that the bottom image needs to be updated.
     */

    /**
     * @var openvrml::viewer::object_t background_node::viewerObject
     *
     * @brief Handle for the renderer.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    background_node::
    background_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<background_node>(type, scope),
        child_node(type, scope),
        set_bind_listener_(*this),
        ground_angle_(*this),
        ground_color_(*this),
        back_url_(*this),
        bottom_url_(*this),
        front_url_(*this),
        left_url_(*this),
        right_url_(*this),
        top_url_(*this),
        sky_angle_(*this),
        sky_color_(*this, std::vector<color>(1, color(0.0, 0.0, 0.0))),
        is_bound_emitter_(*this, this->is_bound_),
        front_needs_update(true),
        back_needs_update(true),
        left_needs_update(true),
        right_needs_update(true),
        top_needs_update(true),
        bottom_needs_update(true),
        viewerObject(0)
    {}

    /**
     * @brief Destroy.
     */
    background_node::~background_node() throw ()
    {
        // remove d_viewerObject...
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     */
    void background_node::do_initialize(double) throw ()
    {
        assert(dynamic_cast<const background_class *>(
                   &this->type().node_class()));
        background_class & nodeClass =
            const_cast<background_class &>(
                static_cast<const background_class &>(
                    this->type().node_class()));
        if (!nodeClass.has_first()) { nodeClass.set_first(*this); }
    }

    /**
     * @brief Shut down.
     *
     * Calls background_class::unbind to unbind the node if it is bound.
     *
     * @param timestamp the current time.
     */
    void
    background_node::do_shutdown(const double timestamp)
        throw ()
    {
        background_class & node_class =
            const_cast<background_class &>(
                static_cast<const background_class &>(
                    this->type().node_class()));
        node_class.unbind(*this, timestamp);

        if (node_class.is_first(*this)) { node_class.reset_first(); }
    }

# ifdef OPENVRML_ENABLE_PNG_TEXTURES
    extern "C" void openvrml_png_info_callback(png_structp png_ptr,
                                               png_infop info_ptr);
    extern "C" void openvrml_png_row_callback(png_structp png_ptr,
                                              png_bytep new_row,
                                              png_uint_32 row_num,
                                              int pass);
    extern "C" void openvrml_png_end_callback(png_structp png_ptr,
                                              png_infop info_ptr);
# endif

# ifdef OPENVRML_ENABLE_JPEG_TEXTURES
    extern "C" void openvrml_jpeg_init_source(j_decompress_ptr cinfo);
    extern "C" boolean openvrml_jpeg_fill_input_buffer(j_decompress_ptr cinfo);
    extern "C" void openvrml_jpeg_skip_input_data(j_decompress_ptr cinfo,
                                                  long num_bytes);
    extern "C" void openvrml_jpeg_term_source(j_decompress_ptr cinfo);
# endif

    class OPENVRML_LOCAL image_stream_listener :
        public openvrml::stream_listener {

        boost::recursive_mutex & node_mutex_;
        openvrml::image & image_;
        openvrml::node & node_;

        class image_reader {
        public:
            virtual ~image_reader() throw () = 0;
            void read(const std::vector<unsigned char> & data);

        private:
            virtual void do_read(const std::vector<unsigned char> & data) = 0;
        };

# ifdef OPENVRML_ENABLE_PNG_TEXTURES
        friend void openvrml_png_info_callback(png_structp png_ptr,
                                               png_infop info_ptr);
        friend void openvrml_png_row_callback(png_structp png_ptr,
                                              png_bytep new_row,
                                              png_uint_32 row_num,
                                              int pass);
        friend void openvrml_png_end_callback(png_structp png_ptr,
                                              png_infop info_ptr);

        class png_reader : public image_reader {
            png_structp png_ptr_;
            png_infop info_ptr_;

        public:
            image_stream_listener & stream_listener;
            std::vector<png_byte> old_row;
            bool gray_palette;

            explicit png_reader(image_stream_listener & stream_listener);
            virtual ~png_reader() throw ();

        private:
            virtual void do_read(const std::vector<unsigned char> & data);
        };
# endif

# ifdef OPENVRML_ENABLE_JPEG_TEXTURES
        friend void openvrml_jpeg_init_source(j_decompress_ptr cinfo);
        friend boolean openvrml_jpeg_fill_input_buffer(j_decompress_ptr cinfo);
        friend void openvrml_jpeg_skip_input_data(j_decompress_ptr cinfo,
                                                  long num_bytes);
        friend void openvrml_jpeg_term_source(j_decompress_ptr cinfo);

        class jpeg_reader : public image_reader {
        public:
            struct source_mgr {
                jpeg_source_mgr pub;
                jpeg_reader * reader;
            };

        private:
            jpeg_decompress_struct cinfo_;
            struct error_mgr {
                jpeg_error_mgr pub;
                jmp_buf jmpbuf;
            } error_mgr_;
            source_mgr source_mgr_;

        public:
            image_stream_listener & stream_listener;
            enum read_state_t {
                reading_back = 0,
                reading_new
            } read_state;
            size_t bytes_to_skip;
            size_t backtrack_buffer_bytes_unread;
            std::vector<JOCTET> buffer, backtrack_buffer;
            enum decoder_state_t {
                header,
                start_decompress,
                decompress_progressive,
                decompress_sequential,
                done,
                sink_non_jpeg_trailer,
                error
            } decoder_state;
            JSAMPARRAY scanlines;
            bool progressive_scan_started;

            explicit jpeg_reader(image_stream_listener & stream_listener);
            virtual ~jpeg_reader() throw ();

        private:
            virtual void do_read(const std::vector<unsigned char> & data);

            bool output_scanlines();
        };
# endif

        boost::scoped_ptr<image_reader> image_reader_;

    public:
        image_stream_listener(openvrml::image & image,
                              openvrml::node & node,
                              boost::recursive_mutex & node_mutex);
        virtual ~image_stream_listener() throw ();

    private:
        virtual void
        do_stream_available(const std::string & uri,
                            const std::string & media_type);

        virtual void
        do_data_available(const std::vector<unsigned char> & data);
    };

    image_stream_listener::image_reader::~image_reader() throw ()
    {}

    void
    image_stream_listener::image_reader::
    read(const std::vector<unsigned char> & data)
    {
        this->do_read(data);
    }

# ifdef OPENVRML_ENABLE_PNG_TEXTURES
    void openvrml_png_info_callback(png_structp png_ptr, png_infop info_ptr)
    {
        typedef image_stream_listener::png_reader png_reader_t;
        png_reader_t & reader =
            *static_cast<png_reader_t *>(png_get_progressive_ptr(png_ptr));

        boost::recursive_mutex::scoped_lock
            lock(reader.stream_listener.node_mutex_);

        openvrml::image & image = reader.stream_listener.image_;

        image.comp(png_get_channels(png_ptr, info_ptr));
        const size_t width = png_get_image_width(png_ptr, info_ptr);
        const size_t height = png_get_image_height(png_ptr, info_ptr);
        image.resize(width, height);

        //
        // Strip 16 bit/color files to 8 bit/color.
        //
        png_set_strip_16(png_ptr);

        //
        // Extract multiple pixels with bit depths of 1, 2, and 4 from a
        // single byte into separate bytes.  (Usefule for paletted and
        // grayscale images.)
        //
        png_set_packing(png_ptr);

        //
        // Expand paletted colors into true RGB triplets.
        //
        const png_byte color_type = png_get_color_type(png_ptr, info_ptr);
        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_expand(png_ptr);
            image.comp(3);
        }

        //
        // Expand grayscale images to the full 8 bits from 1, 2, or
        // 4 bits/pixel.
        //
        const png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
            png_set_expand(png_ptr);
        }

        //
        // Expand paletted or RGB images with transparency to full alpha
        // channels so the data will be available as RGBA quartets.
        //
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
            png_set_expand(png_ptr);
            image.comp(image.comp() + 1);
        }

        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            int num_palette;
            png_colorp palette;
            if (png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette)) {
                reader.gray_palette = true;
                for (int i = 0; i < num_palette; ++i) {
                    if (palette[i].red != palette[i].green
                        || palette[i].blue != palette[i].green) {
                        reader.gray_palette = false;
                        break;
                    }
                }
            }
        }

        if (reader.gray_palette) {
            if (image.comp() == 3) {
                image.comp(1);
            } else if (image.comp() == 4) {
                image.comp(2);
            }
        }

        //
        // Set gamma.
        //
        static const double screen_gamma = 2.2; // Display exponent.
        static const double default_gamma = 0.45455;
        double file_gamma;
        png_set_gamma(png_ptr,
                      screen_gamma,
                      png_get_gAMA(png_ptr, info_ptr, &file_gamma)
                      ? file_gamma
                      : default_gamma);

        png_set_interlace_handling(png_ptr);

        png_read_update_info(png_ptr, info_ptr);

        reader.old_row.resize(image.comp() * image.x());
    }

    void openvrml_png_row_callback(png_structp png_ptr,
                                   png_bytep new_row,
                                   png_uint_32 row_num,
                                   int /* pass */)
    {
        if (!new_row) { return; }

        typedef image_stream_listener::png_reader png_reader_t;
        png_reader_t & reader =
            *static_cast<png_reader_t *>(png_get_progressive_ptr(png_ptr));

        boost::recursive_mutex::scoped_lock
            lock(reader.stream_listener.node_mutex_);

        openvrml::image & image = reader.stream_listener.image_;

        png_progressive_combine_row(png_ptr, &reader.old_row[0], new_row);

        //
        // openvrml::image pixels start at the bottom left.
        //
        const size_t image_row = (image.y() - 1) - row_num;
        const size_t bytes_per_row = reader.old_row.size();
        const size_t image_width = bytes_per_row / image.comp();
        for (size_t pixel_index = 0, byte_index = 0; pixel_index < image_width;
             ++pixel_index) {
            using openvrml::int32;
            int32 pixel = 0x00000000;
            for (size_t component = image.comp();
                 component > 0;
                 --component) {
                pixel |= int32(new_row[byte_index]) << (8 * (component - 1));
                if (reader.gray_palette) {
                    if (image.comp() == 1) {
                        // We just want every third pixel element.
                        byte_index += 3;
                    } else if (image.comp() == 2) {
                        // We just want the first and fourth pixel elements.
                        byte_index += (byte_index % 4 == 0) ? 3 : 1;
                    }
                } else {
                    ++byte_index;
                }
            }
            image.pixel(image_row * image_width + pixel_index, pixel);
        }

        reader.stream_listener.node_.modified(true);

        copy(new_row, new_row + bytes_per_row, reader.old_row.begin());
    }

    void openvrml_png_end_callback(png_structp, png_infop)
    {}

    image_stream_listener::png_reader::
    png_reader(image_stream_listener & stream_listener):
        png_ptr_(0),
        info_ptr_(0),
        stream_listener(stream_listener),
        gray_palette(false)
    {
        using openvrml_::scope_guard;
        using openvrml_::make_guard;

        this->png_ptr_ =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        if (!this->png_ptr_) { throw std::bad_alloc(); }
        scope_guard guard = make_guard(&png_destroy_read_struct,
                                       &this->png_ptr_,
                                       &this->info_ptr_,
                                       png_infopp(0));

        this->info_ptr_ = png_create_info_struct(this->png_ptr_);
        if (!this->info_ptr_) { throw std::bad_alloc(); }

        png_set_progressive_read_fn(this->png_ptr_,
                                    this,
                                    openvrml_png_info_callback,
                                    openvrml_png_row_callback,
                                    openvrml_png_end_callback);
        guard.dismiss();
    }

    image_stream_listener::png_reader::~png_reader() throw ()
    {
        png_destroy_read_struct(&this->png_ptr_,
                                &this->info_ptr_,
                                png_infopp(0));
    }

    void
    image_stream_listener::png_reader::
    do_read(const std::vector<unsigned char> & data)
    {
        int jmpval = setjmp(png_jmpbuf(this->png_ptr_));
        if (jmpval != 0) { return; }

        png_process_data(this->png_ptr_,
                         this->info_ptr_,
                         const_cast<png_byte *>(&data[0]),
                         data.size());
    }
# endif // defined OPENVRML_ENABLE_PNG_TEXTURES

# ifdef OPENVRML_ENABLE_JPEG_TEXTURES
    void openvrml_jpeg_init_source(j_decompress_ptr)
    {}

    boolean openvrml_jpeg_fill_input_buffer(j_decompress_ptr cinfo)
    {
        typedef image_stream_listener::jpeg_reader::source_mgr source_mgr_t;
        source_mgr_t & src =
            *reinterpret_cast<source_mgr_t *>(cinfo->src);

        jpeg_source_mgr & source_mgr = src.pub;
        image_stream_listener::jpeg_reader & reader = *src.reader;

        switch (reader.read_state) {
        case image_stream_listener::jpeg_reader::reading_back:
            if (reader.buffer.empty()) {
                return false; // Suspend.
            }
            if (reader.bytes_to_skip > reader.buffer.size()) {
                reader.bytes_to_skip -= reader.buffer.size();
                reader.buffer.clear();
                return false; // Suspend.
            }

            reader.backtrack_buffer_bytes_unread = source_mgr.bytes_in_buffer;
            {
                std::vector<JOCTET>::iterator pos = reader.buffer.begin();
                advance(pos, reader.bytes_to_skip);
                source_mgr.next_input_byte = &*pos;
            }
            source_mgr.bytes_in_buffer -= reader.bytes_to_skip;
            reader.bytes_to_skip = 0;
            reader.read_state =
                image_stream_listener::jpeg_reader::reading_new;

            return true;

        case image_stream_listener::jpeg_reader::reading_new:
            if (source_mgr.next_input_byte != (reader.buffer.empty()
                                               ? 0 : &reader.buffer[0])) {
                reader.backtrack_buffer_bytes_unread = 0;
                reader.backtrack_buffer.resize(0);
            }

            {
                const size_t old_backtrack_buffer_size =
                    reader.backtrack_buffer.size();

                reader.backtrack_buffer.resize(source_mgr.bytes_in_buffer
                                               + old_backtrack_buffer_size);

                copy(source_mgr.next_input_byte,
                     source_mgr.next_input_byte + source_mgr.bytes_in_buffer,
                     reader.backtrack_buffer.begin()
                     + old_backtrack_buffer_size);

                source_mgr.next_input_byte =
                    &*(reader.backtrack_buffer.begin()
                       + old_backtrack_buffer_size
                       - reader.backtrack_buffer_bytes_unread);
            }
            source_mgr.bytes_in_buffer += reader.backtrack_buffer_bytes_unread;
            reader.read_state =
                image_stream_listener::jpeg_reader::reading_back;
        }
        return false;
    }

    void openvrml_jpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes)
    {
        typedef image_stream_listener::jpeg_reader::source_mgr source_mgr_t;
        source_mgr_t & src =
            *reinterpret_cast<source_mgr_t *>(cinfo->src);

        jpeg_source_mgr & source_mgr = src.pub;
        image_stream_listener::jpeg_reader & reader = *src.reader;

        if (size_t(num_bytes) > source_mgr.bytes_in_buffer) {
            reader.bytes_to_skip = num_bytes - source_mgr.bytes_in_buffer;
            source_mgr.next_input_byte += source_mgr.bytes_in_buffer;
            source_mgr.bytes_in_buffer = 0;
        } else {
            source_mgr.bytes_in_buffer -= num_bytes;
            source_mgr.next_input_byte += num_bytes;
        }
    }

    void openvrml_jpeg_term_source(j_decompress_ptr)
    {}

    image_stream_listener::jpeg_reader::
    jpeg_reader(image_stream_listener & stream_listener):
        stream_listener(stream_listener),
        read_state(reading_back),
        bytes_to_skip(0),
        backtrack_buffer_bytes_unread(0),
        decoder_state(header),
        scanlines(0),
        progressive_scan_started(false)
    {
        //std::memset(&this->cinfo, 0, sizeof this->cinfo_);
        //std::memset(&this->source_mgr_, 0, sizeof this->source_mgr_);

        this->cinfo_.err = jpeg_std_error(&this->error_mgr_.pub);
        int jmpval = setjmp(this->error_mgr_.jmpbuf);
        if (jmpval != 0) { return; }
        jpeg_create_decompress(&this->cinfo_);
        this->source_mgr_.pub.next_input_byte = 0;
        this->source_mgr_.pub.bytes_in_buffer = 0;
        this->source_mgr_.pub.init_source = openvrml_jpeg_init_source;
        this->source_mgr_.pub.fill_input_buffer =
            openvrml_jpeg_fill_input_buffer;
        this->source_mgr_.pub.skip_input_data = openvrml_jpeg_skip_input_data;
        this->source_mgr_.pub.resync_to_restart = jpeg_resync_to_restart;
        this->source_mgr_.pub.term_source = openvrml_jpeg_term_source;
        this->source_mgr_.reader = this;

        this->cinfo_.src =
            reinterpret_cast<jpeg_source_mgr *>(&this->source_mgr_);
    }

    image_stream_listener::jpeg_reader::~jpeg_reader() throw ()
    {
        jpeg_destroy_decompress(&this->cinfo_);
    }

    void
    image_stream_listener::jpeg_reader::
    do_read(const std::vector<unsigned char> & data)
    {
        if (data.size() > this->buffer.size()) {
            this->buffer.resize(data.size());
        }
        copy(data.begin(), data.end(), this->buffer.begin());

        int jmpval = setjmp(this->error_mgr_.jmpbuf);
        if (jmpval != 0) { return; }

        switch (this->decoder_state) {
        case jpeg_reader::header:
        {
            boost::recursive_mutex::scoped_lock
                lock(this->stream_listener.node_mutex_);

            static const bool require_image = true;
            const int read_header_result = jpeg_read_header(&this->cinfo_,
                                                            require_image);
            if (read_header_result == JPEG_SUSPENDED) { return; }

            switch (this->cinfo_.jpeg_color_space) {
            case JCS_GRAYSCALE:
            case JCS_RGB:
            case JCS_YCbCr:
                this->cinfo_.out_color_space = JCS_RGB;
                break;
            default:
                this->decoder_state = jpeg_reader::error;
                return;
            }

            this->cinfo_.buffered_image =
                jpeg_has_multiple_scans(&this->cinfo_);

            jpeg_calc_output_dimensions(&this->cinfo_);

            openvrml::image & image = this->stream_listener.image_;
            image.comp(this->cinfo_.num_components);
            image.resize(this->cinfo_.image_width, this->cinfo_.image_height);

            const JDIMENSION samples_per_row =
                this->cinfo_.output_width * this->cinfo_.num_components;
            static const JDIMENSION num_rows = 1;
            this->scanlines =
                (*this->cinfo_.mem->alloc_sarray)(
                    reinterpret_cast<j_common_ptr>(&this->cinfo_),
                    JPOOL_IMAGE,
                    samples_per_row,
                    num_rows);

            this->decoder_state = jpeg_reader::start_decompress;
        }
        case jpeg_reader::start_decompress:
        {
            this->cinfo_.dct_method = JDCT_ISLOW;
            this->cinfo_.dither_mode = JDITHER_FS;
            this->cinfo_.do_fancy_upsampling = true;
            this->cinfo_.enable_2pass_quant = false;
            this->cinfo_.do_block_smoothing = true;

            if (!jpeg_start_decompress(&this->cinfo_)) {
                return; // Input suspended.
            }

            this->decoder_state = this->cinfo_.buffered_image
                ? jpeg_reader::decompress_progressive
                : jpeg_reader::decompress_sequential;
        }
        case jpeg_reader::decompress_sequential:
            if (this->decoder_state == jpeg_reader::decompress_sequential) {
                if (!this->output_scanlines()) {
                    return; // Input suspended.
                }
                this->decoder_state = jpeg_reader::done;
            }
        case jpeg_reader::decompress_progressive:
            if (this->decoder_state == jpeg_reader::decompress_progressive) {
                int status;
                do {
                    status = jpeg_consume_input(&this->cinfo_);
                } while (status != JPEG_SUSPENDED
                         && status != JPEG_REACHED_EOI);

                while (true) {
                    if (this->cinfo_.output_scanline == 0
                        && !this->progressive_scan_started) {
                        int scan = this->cinfo_.input_scan_number;

                        if (this->cinfo_.output_scan_number == 0
                            && scan > 1
                            && status != JPEG_REACHED_EOI) {
                            --scan;
                        }

                        if (!jpeg_start_output(&this->cinfo_, scan)) {
                            return; // Input suspended.
                        }
                        this->progressive_scan_started = true;
                    }

                    if (!this->output_scanlines()) {
                        return; // Input suspended.
                    }

                    if (this->cinfo_.output_scanline
                        == this->cinfo_.output_height) {
                        if (!jpeg_finish_output(&this->cinfo_)) {
                            return; // Input suspended.
                        }
                        if (jpeg_input_complete(&this->cinfo_)
                            && (this->cinfo_.input_scan_number
                                == this->cinfo_.output_scan_number)) {
                            break;
                        }
                        this->cinfo_.output_scanline = 0;
                        this->progressive_scan_started = false;
                    }
                }

                this->decoder_state = jpeg_reader::done;
            }
        case jpeg_reader::done:
            if (!jpeg_finish_decompress(&this->cinfo_)) {
                return; // Input suspended.
            }
            this->decoder_state = jpeg_reader::sink_non_jpeg_trailer;
            break;

        case jpeg_reader::sink_non_jpeg_trailer:
            break;

        case jpeg_reader::error:
            break;
        }
    }

    bool image_stream_listener::jpeg_reader::output_scanlines()
    {
        boost::recursive_mutex::scoped_lock
            lock(this->stream_listener.node_mutex_);

        JDIMENSION top = this->cinfo_.output_scanline;
        bool result = true;

        openvrml::image & image = this->stream_listener.image_;

        while (this->cinfo_.output_scanline < this->cinfo_.output_height) {
            JDIMENSION scanlines_completed =
                jpeg_read_scanlines(&this->cinfo_, this->scanlines, 1);
            if (scanlines_completed != 1) {
                result = false; // Suspend.
                break;
            }

            const size_t image_row = image.y() - this->cinfo_.output_scanline;
            for (size_t pixel_index = 0, byte_index = 0;
                 pixel_index < image.x();
                 ++pixel_index) {
                using openvrml::int32;
                int32 pixel = 0x00000000;
                for (size_t component = image.comp();
                     component > 0;
                     --component, ++byte_index) {
                    const JSAMPLE sample = (*this->scanlines)[byte_index];
                    pixel |= int32(sample) << (8 * (component - 1));
                }
                image.pixel(image_row * image.x() + pixel_index, pixel);
            }
        }

        if (top != this->cinfo_.output_scanline) {
            this->stream_listener.node_.modified(true);
        }

        return result;
    }
# endif // defined OPENVRML_ENABLE_JPEG_TEXTURES

    image_stream_listener::
    image_stream_listener(openvrml::image & image,
                          openvrml::node & node,
                          boost::recursive_mutex & node_mutex):
        node_mutex_(node_mutex),
        image_(image),
        node_(node)
    {}

    image_stream_listener::~image_stream_listener() throw ()
    {}

    void
    image_stream_listener::do_stream_available(const std::string & /* uri */,
                                               const std::string & media_type)
    {
        using boost::algorithm::iequals;
        if (iequals(media_type, "image/png")
            || iequals(media_type, "image/x-png")) {
# ifdef OPENVRML_ENABLE_PNG_TEXTURES
            this->image_reader_.reset(new png_reader(*this));
# endif
        } else if (iequals(media_type, "image/jpeg")) {
# ifdef OPENVRML_ENABLE_JPEG_TEXTURES
            this->image_reader_.reset(new jpeg_reader(*this));
# endif
        }
    }

    void
    image_stream_listener::
    do_data_available(const std::vector<unsigned char> & data)
    {
        if (this->image_reader_) { this->image_reader_->read(data); }
    }

    /**
     * @brief Called lazily to update texture data.
     */
    void background_node::update_textures()
    {
        if (this->front_needs_update) {
            if (this->front_url_.mfstring::value().empty()) {
                this->front = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->front_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->front,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->front_needs_update = false;
        }
        if (this->back_needs_update) {
            if (this->back_url_.mfstring::value().empty()) {
                this->back = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->back_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->back,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->back_needs_update = false;
        }
        if (this->left_needs_update) {
            if (this->left_url_.mfstring::value().empty()) {
                this->left = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->left_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->left,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->left_needs_update = false;
        }
        if (this->right_needs_update) {
            if (this->right_url_.mfstring::value().empty()) {
                this->right = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->right_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->right,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->right_needs_update = false;
        }
        if (this->top_needs_update) {
            if (this->top_url_.mfstring::value().empty()) {
                this->top = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->top_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->top,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->top_needs_update = false;
        }
        if (this->bottom_needs_update) {
            if (this->bottom_url_.mfstring::value().empty()) {
                this->bottom = image();
            } else {
                using std::auto_ptr;
                auto_ptr<resource_istream>
                    in(this->scene()
                       ->get_resource(this->bottom_url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->bottom,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->bottom_needs_update = false;
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    billboard_class::
    billboard_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    billboard_class::~billboard_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Billboard nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by billboard_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    billboard_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 6> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "addChildren"),
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "removeChildren"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "axisOfRotation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "children"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize")
        };

        typedef node_type_impl<billboard_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & billboardNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                billboardNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        billboard_node::add_children_listener>(
                            &billboard_node::add_children_listener_)));
            } else if (*interface == *++supported_interface) {
                billboardNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        billboard_node::remove_children_listener>(
                            &billboard_node::remove_children_listener_)));
            } else if (*interface == *++supported_interface) {
                billboardNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<billboard_node>::exposedfield<sfvec3f> >(
                            &billboard_node::axis_of_rotation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<billboard_node>::exposedfield<sfvec3f> >(
                            &billboard_node::axis_of_rotation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<billboard_node>::exposedfield<sfvec3f> >(
                            &billboard_node::axis_of_rotation_)));
            } else if (*interface == *++supported_interface) {
                billboardNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        billboard_node::children_exposedfield>(
                            &billboard_node::children_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        billboard_node::children_exposedfield>(
                            &billboard_node::children_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        billboard_node::children_exposedfield>(
                            &billboard_node::children_)));
            } else if (*interface == *++supported_interface) {
                billboardNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &billboard_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                billboardNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &billboard_node::bbox_size_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class billboard_node
     *
     * @brief Billboard node instances.
     */

    /**
     * @var billboard_node::billboard_class
     *
     * @brief Class object for Billboard nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<billboard_node>::exposedfield<openvrml::sfvec3f> billboard_node::axis_of_rotation_
     *
     * @brief axisOfRotation exposedField.
     */

    /**
     * @var openvrml::viewer::object_t billboard_node::xformObject
     *
     * @brief Handle for the renderer.
     */

    /**
     * @brief Get the bounding box transformation matrix.
     *
     * @param node      a pointer to a billboard_node.
     * @param modelview input ModelView transformation matrix.
     *
     * @return the bounding box transformation matrix.
     */
    const openvrml::mat4f
    billboard_node::
    billboard_to_matrix(const billboard_node & node, const mat4f & modelview)
    {
        const mat4f inverse_modelview = modelview.inverse();

        mat4f result;

        // Viewer position in local coordinate system
        const vec3f position = vec3f(inverse_modelview[3][0],
                                     inverse_modelview[3][1],
                                     inverse_modelview[3][2]).normalize();

        // Viewer-alignment
        if ((node.axis_of_rotation_.sfvec3f::value()[0] == 0)
            && (node.axis_of_rotation_.sfvec3f::value()[1] == 0)
            && (node.axis_of_rotation_.sfvec3f::value()[2] == 0)) {
            //
            // Viewer's up vector
            //
            const vec3f up = vec3f(inverse_modelview[1][0],
                                   inverse_modelview[1][1],
                                   inverse_modelview[1][2]).normalize();

            // get x-vector from the cross product of Viewer's
            // up vector and billboard-to-viewer vector.
            const vec3f X = up * position;

            result[0][0] = X[0];
            result[0][1] = X[1];
            result[0][2] = X[2];
            result[0][3] = 0.0;

            result[1][0] = up[0];
            result[1][1] = up[1];
            result[1][2] = up[2];
            result[1][3] = 0.0;

            result[2][0] = position[0];
            result[2][1] = position[1];
            result[2][2] = position[2];
            result[2][3] = 0.0;

            result[3][0] = 0.0;
            result[3][1] = 0.0;
            result[3][2] = 0.0;
            result[3][3] = 1.0;
        } else { // use axis of rotation
            // axis of rotation will be the y-axis vector
            const vec3f Y(node.axis_of_rotation_.sfvec3f::value());

            // Plane defined by the axisOfRotation and billboard-to-viewer vector
            const vec3f X = (Y * position).normalize();

            // Get Z axis vector from cross product of X and Y
            const vec3f Z = X * Y;

            // Transform Z axis vector of current coordinate system to new
            // coordinate system.
            float nz[3] = { X[2], Y[2], Z[2] };

            // calculate the angle by which the Z axis vector of current coordinate
            // system has to be rotated around the Y axis to new coordinate system.
            float angle = float(acos(nz[2]));
            if(nz[0] > 0) { angle = -angle; }
            result = mat4f::rotation(rotation(Y, angle));
        }
        return result;
    }

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    billboard_node::
    billboard_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        grouping_node_base<billboard_node>(type, scope),
        axis_of_rotation_(*this, vec3f(0.0, 1.0, 0.0)),
        xformObject(0)
    {}

    /**
     * @brief Destroy.
     */
    billboard_node::~billboard_node() throw ()
    {
        // delete xformObject...
    }

    /**
     * @brief Render the node.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     */
    void
    billboard_node::
    do_render_child(openvrml::viewer & viewer, rendering_context context)
    {
        mat4f new_LM = context.matrix();
        mat4f LM = billboard_to_matrix(*this, new_LM);
        new_LM = LM * new_LM;
        context.matrix(new_LM);

        if (this->xformObject && this->modified()) {
            viewer.remove_object(this->xformObject);
            this->xformObject = 0;
        }

        if (this->xformObject) {
            viewer.insert_reference(this->xformObject);
        } else if (this->children_.mfnode::value().size() > 0) {
            this->xformObject = viewer.begin_object(this->id().c_str());

            viewer.transform(LM);

            // Render children
            this->grouping_node_base<billboard_node>::do_render_child(viewer,
                                                                      context);

            viewer.end_object();
        }

        this->node::modified(false);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    box_class::box_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    box_class::~box_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Box nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by box_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    box_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface supportedInterface =
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "size");

        typedef node_type_impl<box_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & boxNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                boxNodeType.add_field(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(&box_node::size)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class box_node
     *
     * @brief Box node instances.
     */

    /**
     * @var box_node::box_class
     *
     * @brief Class object for Box nodes.
     */

    /**
     * @var openvrml::sfvec3f box_node::size
     *
     * @brief size field.
     */

    /**
     * @var openvrml::bounding_sphere box_node::bsphere
     *
     * @brief Bounding volume.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    box_node::
    box_node(const node_type & type,
             const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<box_node>(type, scope),
        geometry_node(type, scope),
        size(vec3f(2.0, 2.0, 2.0))
    {
        this->bounding_volume_dirty(true); // lazy calc of bvolume
    }

    /**
     * @brief Destroy.
     */
    box_node::~box_node() throw ()
    {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     *
     * @return display object identifier.
     */
    openvrml::viewer::object_t
    box_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        const viewer::object_t object_ref =
            viewer.insert_box(this->size.value());
        return object_ref;
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    box_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const vec3f corner = this->size.value() / 2.0f;
            const float r = corner.length();
            const_cast<box_node *>(this)->bsphere.radius(r);
            const_cast<box_node *>(this)->bounding_volume_dirty(false); // logical const
        }
        return this->bsphere;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    collision_class::
    collision_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    collision_class::~collision_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Collision nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by collision_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    collision_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "addChildren"),
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "removeChildren"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "children"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "collide"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize"),
            node_interface(node_interface::field_id,
                           field_value::sfnode_id,
                           "proxy"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "collideTime")
        };

        typedef node_type_impl<collision_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & collisionNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                collisionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        collision_node::add_children_listener>(
                            &collision_node::add_children_listener_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        collision_node::remove_children_listener>(
                            &collision_node::remove_children_listener_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        collision_node::children_exposedfield>(
                            &collision_node::children_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        collision_node::children_exposedfield>(
                            &collision_node::children_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        collision_node::children_exposedfield>(
                            &collision_node::children_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<collision_node>::exposedfield<sfbool> >(
                            &collision_node::collide_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<collision_node>::exposedfield<sfbool> >(
                            &collision_node::collide_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<collision_node>::exposedfield<sfbool> >(
                            &collision_node::collide_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &collision_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &collision_node::bbox_size_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfnode>(
                            &collision_node::proxy_)));
            } else if (*interface == *++supported_interface) {
                collisionNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<collision_node>::sftime_emitter>(
                            &collision_node::collide_time_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class collision_node
     *
     * @brief Collision node instances.
     */

    /**
     * @var collision_node::collision_class
     *
     * @brief Class object for Collision nodes.
     */

    /**
     * @var openvrml::sfbool collision_node::collide_
     *
     * @brief collide exposedField.
     */

    /**
     * @var openvrml::sfnode collision_node::proxy_
     *
     * @brief proxy field.
     */

    /**
     * @var openvrml::sftime collision_node::collide_time_
     *
     * @brief collideTime eventOut.
     */

    /**
     * @var openvrml::sftime_emitter collision_node::collide_time_emitter_
     *
     * @brief collideTime eventOut.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    collision_node::
    collision_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        grouping_node_base<collision_node>(type, scope),
        collide_(*this, true),
        collide_time_emitter_(*this, this->collide_time_)
    {}

    /**
     * @brief Destroy.
     */
    collision_node::~collision_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool collision_node::modified() const
    {
        return (this->proxy_.value() && this->proxy_.value()->modified())
            || this->grouping_node_base<collision_node>::modified();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    color_class::color_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    color_class::~color_class() throw () {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Color nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by color_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    color_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface supportedInterface =
            node_interface(node_interface::exposedfield_id,
                           field_value::mfcolor_id,
                           "color");

        typedef node_type_impl<color_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & colorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                colorNodeType.add_exposedfield(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<color_node>::exposedfield<mfcolor> >(
                            &color_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<color_node>::exposedfield<mfcolor> >(
                            &color_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<color_node>::exposedfield<mfcolor> >(
                            &color_node::color_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class color_node
     *
     * @brief Color node instances.
     */

    /**
     * @var color_node::color_class
     *
     * @brief Class object for Color nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<color_node>::exposedfield<openvrml::mfcolor> color_node::color_
     *
     * @brief color exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope the scope to which the node belongs.
     */
    color_node::
    color_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<color_node>(type, scope),
        openvrml::color_node(type, scope),
        color_(*this)
    {}

    /**
     * @brief Destroy.
     */
    color_node::~color_node() throw ()
    {}

    /**
     * @brief Get the color array.
     *
     * @return the color array associated with the node.
     */
    const std::vector<openvrml::color> &
    color_node::color() const throw ()
    {
        return this->color_.mfcolor::value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    color_interpolator_class::
    color_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    color_interpolator_class::~color_interpolator_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating ColorInterpolator nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  color_interpolator_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    color_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sffloat_id,
                           "set_fraction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "key"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfcolor_id,
                           "keyValue"),
            node_interface(node_interface::eventout_id,
                           field_value::sfcolor_id,
                           "value_changed")
        };

        typedef node_type_impl<color_interpolator_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & colorInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                colorInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        color_interpolator_node::set_fraction_listener>(
                            &color_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
                colorInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mffloat> >(
                            &color_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mffloat> >(
                            &color_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mffloat> >(
                            &color_interpolator_node::key_)));
            } else if (*interface == *++supported_interface) {
                colorInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mfcolor> >(
                            &color_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mfcolor> >(
                            &color_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<color_interpolator_node>::
                        exposedfield<mfcolor> >(
                            &color_interpolator_node::key_value_)));
            } else if (*interface == *++supported_interface) {
                colorInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<color_interpolator_node>::sfcolor_emitter>(
                            &color_interpolator_node::value_changed_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class color_interpolator_node
     *
     * @brief ColorInterpolator node instances.
     */

    /**
     * @var color_interpolator_node::color_interpolator_class
     *
     * @brief Class object for ColorInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class color_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node color_interpolator_node.
     */
    color_interpolator_node::set_fraction_listener::
    set_fraction_listener(color_interpolator_node & node):
        node_event_listener(node),
        event_listener_base<color_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    color_interpolator_node::set_fraction_listener::
    ~set_fraction_listener()
        throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param value     new fraction value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    color_interpolator_node::set_fraction_listener::
    do_process_event(const sffloat & value, const double timestamp)
        throw (std::bad_alloc)
    {
        using std::vector;

        try {
            color_interpolator_node & node =
                dynamic_cast<color_interpolator_node &>(this->node());

            float fraction = value.value();

            vector<float>::size_type n = node.key_.mffloat::value().size() - 1;
            if (fraction < node.key_.mffloat::value()[0]) {
                node.value_.value(node.key_value_.mfcolor::value()[0]);
            } else if (fraction > node.key_.mffloat::value()[n]) {
                node.value_.value(node.key_value_.mfcolor::value()[n]);
            } else {
                // convert to HSV for the interpolation...
                for (vector<float>::size_type i = 0; i < n; ++i) {
                    if (node.key_.mffloat::value()[i] <= value.value()
                        && fraction <= node.key_.mffloat::value()[i + 1]) {
                        const color & rgb1 =
                            node.key_value_.mfcolor::value()[i];
                        const color & rgb2 =
                            node.key_value_.mfcolor::value()[i + 1];

                        fraction = (fraction - node.key_.mffloat::value()[i])
                            / (node.key_.mffloat::value()[i + 1]
                               - node.key_.mffloat::value()[i]);
                        float hsv1[3], hsv2[3];
                        rgb1.hsv(hsv1);
                        rgb2.hsv(hsv2);

                        // Interpolate angles via the shortest direction
                        if (fabs(hsv2[0] - hsv1[0]) > 180.0) {
                            if (hsv2[0] > hsv1[0]) {
                                hsv1[0] += 360.0;
                            } else {
                                hsv2[0] += 360.0;
                            }
                        }
                        float h = hsv1[0] + fraction * (hsv2[0] - hsv1[0]);
                        float s = hsv1[1] + fraction * (hsv2[1] - hsv1[1]);
                        float v = hsv1[2] + fraction * (hsv2[2] - hsv1[2]);
                        if (h >= 360.0) {
                            h -= 360.0;
                        } else if (h < 0.0) {
                            h += 360.0;
                        }
                        color val = node.value_.value();
                        val.hsv(h, s, v);
                        node.value_.value(val);
                        break;
                    }
                }
            }
            node.emit_event(node.value_changed_, timestamp);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var color_interpolator_node::set_fraction_listener color_interpolator_node::set_fraction_listener_;
     *
     * @brief set_fraction event handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<color_interpolator_node>::exposedfield<openvrml::mffloat> color_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<color_interpolator_node>::exposedfield<openvrml::mfcolor> color_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::sfcolor color_interpolator_node::value_
     *
     * @brief Current sfcolor value.
     */

    /**
     * @var openvrml::sfcolor_emitter color_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    color_interpolator_node::
    color_interpolator_node(const node_type & type,
                            const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<color_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_(*this, this->value_)
    {}

    /**
     * @brief Destroy.
     */
    color_interpolator_node::~color_interpolator_node()
        throw ()
    {}



    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    cone_class::cone_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    cone_class::~cone_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Cone nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by cone_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    cone_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "bottomRadius"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "height"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "side"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "bottom")
        };

        typedef node_type_impl<cone_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & coneNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                coneNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &cone_node::bottomRadius)));
            } else if (*interface == *++supported_interface) {
                coneNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &cone_node::height)));
            } else if (*interface == *++supported_interface) {
                coneNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &cone_node::side)));
            } else if (*interface == *++supported_interface) {
                coneNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &cone_node::bottom)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class cone_node
     *
     * @brief Cone node instances.
     */

    /**
     * @var cone_node::cone_class
     *
     * @brief Class object for Cone nodes.
     */

    /**
     * @var openvrml::sfbool cone_node::bottom
     *
     * @brief bottom field.
     */

    /**
     * @var openvrml::sffloat cone_node::bottomRadius
     *
     * @brief bottomRadius field.
     */

    /**
     * @var openvrml::sffloat cone_node::height
     *
     * @brief height field.
     */

    /**
     * @var openvrml::sfbool cone_node::side
     *
     * @brief side field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    cone_node::
    cone_node(const node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<cone_node>(type, scope),
        geometry_node(type, scope),
        bottom(true),
        bottomRadius(1.0),
        height(2.0),
        side(true)
    {}

    /**
     * @brief Destroy.
     */
    cone_node::~cone_node() throw ()
    {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    cone_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        const viewer::object_t object_ref =
            viewer.insert_cone(this->height.value(),
                               this->bottomRadius.value(),
                               this->bottom.value(),
                               this->side.value());
        return object_ref;
    }



    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    coordinate_class::
    coordinate_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_class::~coordinate_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Coordinate nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by coordinate_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    coordinate_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface supportedInterface =
            node_interface(node_interface::exposedfield_id,
                           field_value::mfvec3f_id,
                           "point");

        typedef node_type_impl<coordinate_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & coordinateNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                coordinateNodeType.add_exposedfield(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<coordinate_node>::exposedfield<mfvec3f> >(
                            &coordinate_node::point_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<coordinate_node>::exposedfield<mfvec3f> >(
                            &coordinate_node::point_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<coordinate_node>::exposedfield<mfvec3f> >(
                            &coordinate_node::point_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class coordinate_node
     *
     * @brief Coordinate node instances.
     */

    /**
     * @var coordinate_node::coordinate_class
     *
     * @brief Class object for Coordinate nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_node>::exposedfield<openvrml::mfvec3f> coordinate_node::point_
     *
     * @brief point exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    coordinate_node::
    coordinate_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<coordinate_node>(type, scope),
        openvrml::coordinate_node(type, scope),
        point_(*this)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_node::~coordinate_node() throw ()
    {}

    /**
     * @brief Get the points encapsulated by this node.
     *
     * @return the array of points for this node.
     */
    const std::vector<openvrml::vec3f> &
    coordinate_node::point() const throw ()
    {
        return this->point_.mfvec3f::value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    coordinate_interpolator_class::
    coordinate_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_interpolator_class::
    ~coordinate_interpolator_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating CoordinateInterpolator nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  coordinate_interpolator_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    coordinate_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
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
                           field_value::mfvec3f_id,
                           "value_changed")
        };

        typedef node_type_impl<coordinate_interpolator_node>
            node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & coordinateInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                coordinateInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        coordinate_interpolator_node::set_fraction_listener>(
                            &coordinate_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
                coordinateInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mffloat> >(
                            &coordinate_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mffloat> >(
                            &coordinate_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mffloat> >(
                            &coordinate_interpolator_node::key_)));
            } else if (*interface == *++supported_interface) {
                coordinateInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &coordinate_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &coordinate_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &coordinate_interpolator_node::key_value_)));
            } else if (*interface == *++supported_interface) {
                coordinateInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<coordinate_interpolator_node>::
                        mfvec3f_emitter>(
                            &coordinate_interpolator_node::value_changed_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class coordinate_interpolator_node
     *
     * @brief CoordinateInterpolator node instances.
     */

    /**
     * @var class coordinate_interpolator_node::coordinate_interpolator_class
     *
     * @brief Class object for CoordinateInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class coordinate_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  coordinate_interpolator_node.
     */
    coordinate_interpolator_node::set_fraction_listener::
    set_fraction_listener(coordinate_interpolator_node & node):
        node_event_listener(node),
        event_listener_base<coordinate_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_interpolator_node::set_fraction_listener::
    ~set_fraction_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param fraction  fraction value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    coordinate_interpolator_node::set_fraction_listener::
    do_process_event(const sffloat & fraction, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            using std::vector;

            coordinate_interpolator_node & node =
                dynamic_cast<coordinate_interpolator_node &>(this->node());

            const vector<float> & key = node.key_.mffloat::value();
            const vector<vec3f> & key_value = node.key_value_.mfvec3f::value();
            vector<vec3f> value;;

            size_t nCoords = key_value.size() / key.size();
            size_t n = key.size() - 1;

            if (fraction.value() < key[0]) {
                value.assign(key_value.begin(), key_value.begin() + nCoords);
            } else if (fraction.value() > key[n]) {
                value.assign(key_value.begin() + n * nCoords,
                             key_value.begin() + (n + 1) * nCoords);
            } else {
                // Reserve enough space for the new value
                value.resize(nCoords);

                for (size_t i = 0; i < n; ++i) {
                    if (key[i] <= fraction.value()
                        && fraction.value() <= key[i + 1]) {
                        vector<vec3f>::const_iterator v1 =
                            key_value.begin() + i * nCoords;
                        vector<vec3f>::const_iterator v2 =
                            key_value.begin() + (i + 1) * nCoords;

                        const float f =
                            (fraction.value() - key[i])
                            / (key[i + 1] - key[i]);

                        for (size_t j = 0; j < nCoords; ++j) {
                            value[j] = *v1 + (f * (*v2 - *v1));
                            ++v1;
                            ++v2;
                        }
                        break;
                    }
                }
            }

            node.value_.mfvec3f::value(value);

            // Send the new value
            node::emit_event(node.value_changed_, timestamp);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var coordinate_interpolator_node::set_fraction_listener coordinate_interpolator_node::set_fraction_listener_
     *
     * @brief set_fraction event handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_interpolator_node>::exposedfield<openvrml::mffloat> coordinate_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<coordinate_interpolator_node>::exposedfield<openvrml::mfvec3f> coordinate_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::mfvec3f coordinate_interpolator_node::value_
     *
     * @brief Current value.
     */

    /**
     * @var openvrml::mfvec3f_emitter coordinate_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    coordinate_interpolator_node::
    coordinate_interpolator_node(
        const node_type & type,
        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<coordinate_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_(*this, this->value_)
    {}

    /**
     * @brief Destroy.
     */
    coordinate_interpolator_node::
    ~coordinate_interpolator_node() throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    cylinder_class::
    cylinder_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    cylinder_class::~cylinder_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Cylinder nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by cylinder_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    cylinder_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 5> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "bottom"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "height"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "radius"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "side"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "top")
        };

        typedef node_type_impl<cylinder_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & cylinderNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                cylinderNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &cylinder_node::bottom)));
            } else if (*interface == *++supported_interface) {
                cylinderNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &cylinder_node::height)));
            } else if (*interface == *++supported_interface) {
                cylinderNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &cylinder_node::radius)));
            } else if (*interface == *++supported_interface) {
                cylinderNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &cylinder_node::side)));
            } else if (*interface == *++supported_interface) {
                cylinderNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &cylinder_node::top)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class cylinder_node
     *
     * @brief Cylinder node instances.
     */

    /**
     * @var cylinder_node::cylinder_class
     *
     * @brief Class object for Cylinder nodes.
     */

    /**
     * @var openvrml::sfbool cylinder_node::bottom
     *
     * @brief bottom field.
     */

    /**
     * @var openvrml::sffloat cylinder_node::height
     *
     * @brief height field.
     */

    /**
     * @var openvrml::sffloat cylinder_node::radius
     *
     * @brief radius field.
     */

    /**
     * @var openvrml::sfbool cylinder_node::side
     *
     * @brief side field.
     */

    /**
     * @var openvrml::sfbool cylinder_node::top
     *
     * @brief top field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    cylinder_node::
    cylinder_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<cylinder_node>(type, scope),
        geometry_node(type, scope),
        bottom(true),
        height(2.0),
        radius(1.0),
        side(true),
        top(true)
    {}

    /**
     * @brief Destroy.
     */
    cylinder_node::~cylinder_node() throw ()
    {
        // need access to viewer to remove d_viewerObject...
    }

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    cylinder_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        const viewer::object_t object_ref =
            viewer.insert_cylinder(this->height.value(),
                                   this->radius.value(),
                                   this->bottom.value(),
                                   this->side.value(),
                                   this->top.value());
        return object_ref;
    }



    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    cylinder_sensor_class::
    cylinder_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    cylinder_sensor_class::~cylinder_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating CylinderSensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by cylinder_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    cylinder_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 9> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "autoOffset"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "diskAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "maxAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "minAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "offset"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sfrotation_id,
                           "rotation_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "trackPoint_changed")
        };

        typedef node_type_impl<cylinder_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & cylinderSensorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::auto_offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::auto_offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::auto_offset_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::disk_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::disk_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::disk_angle_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sfbool> >(
                            &cylinder_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::max_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::max_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::max_angle_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::min_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::min_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::min_angle_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::
                        exposedfield<sffloat> >(
                            &cylinder_sensor_node::offset_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::sfbool_emitter>(
                            &cylinder_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::sfrotation_emitter>(
                            &cylinder_sensor_node::rotation_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                cylinderSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<cylinder_sensor_node>::sfvec3f_emitter>(
                            &cylinder_sensor_node::track_point_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class cylinder_sensor_node
     *
     * @brief CylinderSensor node instances.
     */

    /**
     * @var cylinder_sensor_node::cylinder_sensor_class
     *
     * @brief Class object for CylinderSensor nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sfbool> cylinder_sensor_node::auto_offset_
     *
     * @brief autoOffset exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sffloat> cylinder_sensor_node::disk_angle_
     *
     * @brief diskAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sfbool> cylinder_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sffloat> cylinder_sensor_node::max_angle_
     *
     * @brief maxAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sffloat> cylinder_sensor_node::min_angle_
     *
     * @brief minAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<cylinder_sensor_node>::exposedfield<openvrml::sffloat> cylinder_sensor_node::offset_
     *
     * @brief offset exposedField.
     */

    /**
     * @var openvrml::sfbool cylinder_sensor_node::is_active_
     *
     * @brief Active state.
     */

    /**
     * @var openvrml::sfbool_emitter cylinder_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut.
     */

    /**
     * @var openvrml::sfrotation cylinder_sensor_node::rotation_changed_
     *
     * @brief Rotation state.
     */

    /**
     * @var openvrml::sfrotation_emitter cylinder_sensor_node::rotation_changed_emitter_
     *
     * @brief rotation_changed eventOut.
     */

    /**
     * @var openvrml::sfvec3f cylinder_sensor_node::track_point_changed_
     *
     * @brief Track point state.
     */

    /**
     * @var openvrml::sfvec3f_emitter cylinder_sensor_node::track_point_changed_emitter_
     *
     * @brief trackPoint_changed eventOut.
     */

    /**
     * @var float cylinder_sensor_node::rotation_val
     *
     * @brief The rotation value.
     */

    /**
     * @var openvrml::vec3f cylinder_sensor_node::activationPoint
     *
     * @brief The activation point.
     */

    /**
     * @var bool cylinder_sensor_node::disk
     */

    /**
     * @var openvrml::mat4f cylinder_sensor_node::activationMatrix
     *
     * @brief Activation matrix.
     */

    /**
     * @var openvrml::mat4f cylinder_sensor_node::modelview
     *
     * @brief Modelview matrix.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    cylinder_sensor_node::
    cylinder_sensor_node(const node_type & type,
                         const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<cylinder_sensor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        auto_offset_(*this, true),
        disk_angle_(*this, 0.262f),
        enabled_(*this, true),
        max_angle_(*this, -1.0f),
        min_angle_(*this, 0.0f),
        offset_(*this, 0.0f),
        is_active_emitter_(*this, this->is_active_),
        rotation_changed_emitter_(*this, this->rotation_changed_),
        track_point_changed_emitter_(*this, this->track_point_changed_),
        rotation_val(0.0f),
        disk(false)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    cylinder_sensor_node::~cylinder_sensor_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    cylinder_sensor_node::
    do_render_child(openvrml::viewer &, rendering_context context)
    {
        //
        // Store the modelview matrix which is calculated at the time of
        // rendering in render-context.  This matrix will be in use at the time
        // of activation.
        //
        this->modelview = context.matrix();
    }

    /**
     * @brief Called in response to user interaction.
     */
    void
    cylinder_sensor_node::do_activate(double timestamp,
                                      bool,
                                      bool active,
                                      const double (&p)[3])
    {
        using openvrml_::pi;
        using openvrml_::pi_2;

        if (this->enabled_.sfbool::value()) {
            // Become active
            if (active && !this->is_active_.value()) {
                this->is_active_.value(active);

                // set activation point in local coords
                vec3f v(static_cast<float>(p[0]),
                        static_cast<float>(p[1]),
                        static_cast<float>(p[2]));
                this->activationMatrix = this->modelview.inverse();
                v *= this->activationMatrix;
                this->activationPoint = v;
                // Bearing vector in local coordinate system
                v.x(this->activationMatrix[2][0]);
                v.y(this->activationMatrix[2][1]);
                v.z(this->activationMatrix[2][2]);
                const vec3f bearing = v.normalize();
                const vec3f up(0.0, 1.0, 0.0);
                double ang = acos(bearing.dot(up));
                if (ang > pi_2) { ang = pi - ang; }
                this->disk = (ang < this->disk_angle_.sffloat::value());
                // send message
                node::emit_event(this->is_active_emitter_, timestamp);
            }

            // Become inactive
            else if (!active && this->is_active_.value()) {
                this->is_active_.value(active);
                node::emit_event(this->is_active_emitter_, timestamp);

                // save auto offset of rotation
                if (this->auto_offset_.sfbool::value()) {
                    this->offset_.sffloat::value(rotation_val);
                    node::emit_event(this->offset_, timestamp);
                }
            }

            // Tracking
            else if (active) {
                using openvrml_::fequal;

                // get local coord for touch point
                vec3f Vec(static_cast<float>(p[0]),
                          static_cast<float>(p[1]),
                          static_cast<float>(p[2]));
                Vec = Vec * this->activationMatrix;
                this->track_point_changed_.value(Vec);
                node::emit_event(this->track_point_changed_emitter_,
                                 timestamp);
                vec3f tempv;
                float rot, radius;
                vec3f dir1(Vec[0], 0, Vec[2]);
                radius = this->disk
                    ? 1.0f
                    : dir1.length();
                dir1 = dir1.normalize();
                vec3f dir2(this->activationPoint.x(),
                           0,
                           this->activationPoint.z());
                dir2 = dir2.normalize();
                tempv = dir2 * dir1;
                vec3f cx(tempv);
                cx = cx.normalize();
                if (cx.length() == 0.0) { return; }
                rot = radius * float(acos(dir2.dot(dir1)));
                if (fequal<float>()(cx.y(), -1.0f)) { rot = -rot; }
                if (this->auto_offset_.sfbool::value()) {
                    rot = this->offset_.sffloat::value() + rot;
                }
                if (this->min_angle_.sffloat::value()
                    < this->max_angle_.sffloat::value()) {
                    if (rot < this->min_angle_.sffloat::value()) {
                        rot = this->min_angle_.sffloat::value();
                    } else if (rot > this->max_angle_.sffloat::value()) {
                        rot = this->max_angle_.sffloat::value();
                    }
                }
                this->rotation_val = rot;
                this->rotation_changed_.sfrotation::value(
                    openvrml::rotation(0, 1, 0, rot));

                node::emit_event(this->rotation_changed_emitter_, timestamp);
            }
        }
    }

    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    directional_light_class::
    directional_light_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    directional_light_class::~directional_light_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating DirectionalLight nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  directional_light_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    directional_light_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 5> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "ambientIntensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "direction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "intensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "on")
        };

        typedef node_type_impl<directional_light_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & directionalLightNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface = interfaces.begin();
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                directionalLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::ambient_intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::ambient_intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::ambient_intensity_)));
            } else if (*interface == *++supported_interface) {
                directionalLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfcolor> >(
                            &directional_light_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfcolor> >(
                            &directional_light_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfcolor> >(
                            &directional_light_node::color_)));
            } else if (*interface == *++supported_interface) {
                directionalLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfvec3f> >(
                            &directional_light_node::direction_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfvec3f> >(
                            &directional_light_node::direction_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfvec3f> >(
                            &directional_light_node::direction_)));
            } else if (*interface == *++supported_interface) {
                directionalLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sffloat> >(
                            &directional_light_node::intensity_)));
            } else if (*interface == *++supported_interface) {
                directionalLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfbool> >(&directional_light_node::on_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfbool> >(&directional_light_node::on_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<directional_light_node>::
                        exposedfield<sfbool> >(&directional_light_node::on_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class directional_light_node
     *
     * @brief DirectionalLight node instances.
     */

    /**
     * @var directional_light_node::directional_light_class
     *
     * @brief Class object for DirectionalLight nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<directional_light_node>::exposedfield<openvrml::sfvec3f> directional_light_node::direction_
     *
     * @brief direction exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    directional_light_node::
    directional_light_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        light_node(type, scope),
        abstract_light_node<directional_light_node>(type, scope),
        direction_(*this, vec3f(0.0, 0.0, -1.0))
    {}

    /**
     * @brief Destroy.
     */
    directional_light_node::~directional_light_node()
        throw ()
    {}

    /**
     * @brief Render the node.
     *
     * This should be called before rendering any sibling nodes.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    directional_light_node::
    do_render_child(openvrml::viewer & viewer, rendering_context)
    {
        if (this->on_.sfbool::value()) {
            viewer.insert_dir_light(this->ambient_intensity_.sffloat::value(),
                                    this->intensity_.sffloat::value(),
                                    this->color_.sfcolor::value(),
                                    this->direction_.sfvec3f::value());
        }
        this->node::modified(false);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    elevation_grid_class::
    elevation_grid_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    elevation_grid_class::~elevation_grid_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating ElevationGrid nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by elevation_grid_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    elevation_grid_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 14> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mffloat_id,
                           "set_height"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "normal"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "texCoord"),
            node_interface(node_interface::field_id,
                           field_value::mffloat_id,
                           "height"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "ccw"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "colorPerVertex"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "creaseAngle"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "normalPerVertex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "solid"),
            node_interface(node_interface::field_id,
                           field_value::sfint32_id,
                           "xDimension"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "xSpacing"),
            node_interface(node_interface::field_id,
                           field_value::sfint32_id,
                           "zDimension"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "zSpacing")
        };

        typedef node_type_impl<elevation_grid_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & elevationGridNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                elevationGridNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        elevation_grid_node::set_height_listener>(
                            &elevation_grid_node::set_height_listener_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::color_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::normal_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::normal_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::normal_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::tex_coord_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::tex_coord_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<elevation_grid_node>::exposedfield<sfnode> >(
                            &elevation_grid_node::tex_coord_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mffloat>(
                            &elevation_grid_node::height_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &elevation_grid_node::ccw_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &elevation_grid_node::color_per_vertex_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &elevation_grid_node::crease_angle_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &elevation_grid_node::normal_per_vertex_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &elevation_grid_node::solid_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfint32>(
                            &elevation_grid_node::x_dimension_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &elevation_grid_node::x_spacing_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfint32>(
                            &elevation_grid_node::z_dimension_)));
            } else if (*interface == *++supported_interface) {
                elevationGridNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &elevation_grid_node::z_spacing_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class elevation_grid_node
     *
     * @brief ElevationGrid node instances.
     */

    /**
     * @var elevation_grid_node::elevation_grid_class
     *
     * @brief Class object for ElevationGrid nodes.
     */

    /**
     * @internal
     *
     * @class elevation_grid_node::set_height_listener
     *
     * @brief set_height event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  elevation_grid_node.
     */
    elevation_grid_node::set_height_listener::
    set_height_listener(elevation_grid_node & node):
        node_event_listener(node),
        event_listener_base<elevation_grid_node>(node),
        mffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    elevation_grid_node::set_height_listener::
    ~set_height_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param height    height value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    elevation_grid_node::set_height_listener::
    do_process_event(const mffloat & height, double)
        throw (std::bad_alloc)
    {
        try {
            elevation_grid_node & elevation_grid =
                dynamic_cast<elevation_grid_node &>(this->node());

            elevation_grid.height_ = height;
            elevation_grid.node::modified(true);

        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var elevation_grid_node::set_height_listener elevation_grid_node::set_height_listener_
     *
     * @brief set_height eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<elevation_grid_node>::exposedfield<openvrml::sfnode> elevation_grid_node::color_
     *
     * @brief color exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<elevation_grid_node>::exposedfield<openvrml::sfnode> elevation_grid_node::normal_
     *
     * @brief normal exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<elevation_grid_node>::exposedfield<openvrml::sfnode> elevation_grid_node::tex_coord_
     *
     * @brief texCoord exposedField.
     */

    /**
     * @var openvrml::sfbool elevation_grid_node::ccw_
     *
     * @brief ccw field.
     */

    /**
     * @var openvrml::sfbool elevation_grid_node::color_per_vertex_
     *
     * @brief colorPerVertex field.
     */

    /**
     * @var openvrml::sffloat elevation_grid_node::crease_angle_
     *
     * @brief creaseAngle field.
     */

    /**
     * @var openvrml::mffloat elevation_grid_node::height_
     *
     * @brief height field.
     */

    /**
     * @var openvrml::sfbool elevation_grid_node::normal_per_vertex_
     *
     * @brief normalPerVertex field.
     */

    /**
     * @var openvrml::sfbool elevation_grid_node::solid_
     *
     * @brief solid field.
     */

    /**
     * @var openvrml::sfint32 elevation_grid_node::x_dimension_
     *
     * @brief xDimension field.
     */

    /**
     * @var openvrml::sffloat elevation_grid_node::x_spacing_
     *
     * @brief xSpacing field.
     */

    /**
     * @var openvrml::sfint32 elevation_grid_node::z_dimension_
     *
     * @brief zDimension field.
     */

    /**
     * @var openvrml::sffloat ,elevation_grid_node::z_spacing_
     *
     * @brief zSpacing field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    elevation_grid_node::
    elevation_grid_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<elevation_grid_node>(type, scope),
        geometry_node(type, scope),
        set_height_listener_(*this),
        color_(*this),
        normal_(*this),
        tex_coord_(*this),
        ccw_(true),
        color_per_vertex_(true),
        normal_per_vertex_(true),
        solid_(true),
        x_dimension_(0),
        x_spacing_(1.0f),
        z_dimension_(0),
        z_spacing_(1.0f)
    {}

    /**
     * @brief Destroy.
     */
    elevation_grid_node::~elevation_grid_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool elevation_grid_node::modified() const
    {
        return this->node::modified()
            || (this->color_.sfnode::value()
                && this->color_.sfnode::value()->modified())
            || (this->normal_.sfnode::value()
                && this->normal_.sfnode::value()->modified())
            || (this->tex_coord_.sfnode::value()
                && this->tex_coord_.sfnode::value()->modified());
    }

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    elevation_grid_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        viewer::object_t obj = 0;

        openvrml::color_node * const colorNode =
            node_cast<openvrml::color_node *>(
                this->color_.sfnode::value().get());
        openvrml::normal_node * const normalNode =
            node_cast<openvrml::normal_node *>(
                this->normal_.sfnode::value().get());
        openvrml::texture_coordinate_node * const texCoordNode =
            node_cast<openvrml::texture_coordinate_node *>(
                this->tex_coord_.sfnode::value().get());

        if (!this->height_.mffloat::value().empty()) {
            using std::vector;

            const vector<openvrml::color> & color =
                colorNode
                ? colorNode->color()
                : vector<openvrml::color>();

            const vector<vec3f> & normal =
                normalNode
                ? normalNode->vector()
                : vector<vec3f>();

            const vector<vec2f> & texCoord =
                texCoordNode
                ? texCoordNode->point()
                : vector<vec2f>();
            // insert geometry
            unsigned int optMask = 0;
            if (this->ccw_.value()) {
                optMask |= viewer::mask_ccw;
            }
            if (this->solid_.value()) {
                optMask |= viewer::mask_solid;
            }
            if (this->color_per_vertex_.value()) {
                optMask |= viewer::mask_color_per_vertex;
            }
            if (this->normal_per_vertex_.value()) {
                optMask |= viewer::mask_normal_per_vertex;
            }

            obj =
                viewer.insert_elevation_grid(
                    optMask,
                    this->height_.mffloat::value(),
                    this->x_dimension_.sfint32::value(),
                    this->z_dimension_.sfint32::value(),
                    this->x_spacing_.sffloat::value(),
                    this->z_spacing_.sffloat::value(),
                    color,
                    normal,
                    texCoord);
        }

        if (colorNode) { colorNode->modified(false); }
        if (normalNode) { normalNode->modified(false); }
        if (texCoordNode) { texCoordNode->modified(false); }

        return obj;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    extrusion_class::
    extrusion_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    extrusion_class::~extrusion_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Extrusion nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by extrusion_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    extrusion_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 14> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfvec2f_id,
                           "set_crossSection"),
            node_interface(node_interface::eventin_id,
                           field_value::mfrotation_id,
                           "set_orientation"),
            node_interface(node_interface::eventin_id,
                           field_value::mfvec2f_id,
                           "set_scale"),
            node_interface(node_interface::eventin_id,
                           field_value::mfvec3f_id,
                           "set_spine"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "beginCap"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "ccw"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "convex"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "creaseAngle"),
            node_interface(node_interface::field_id,
                           field_value::mfvec2f_id,
                           "crossSection"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "endCap"),
            node_interface(node_interface::field_id,
                           field_value::mfrotation_id,
                           "orientation"),
            node_interface(node_interface::field_id,
                           field_value::mfvec2f_id,
                           "scale"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "solid"),
            node_interface(node_interface::field_id,
                           field_value::mfvec3f_id,
                           "spine")
        };

        typedef node_type_impl<extrusion_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & extrusionNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                extrusionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        extrusion_node::set_cross_section_listener>(
                            &extrusion_node::set_cross_section_listener_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        extrusion_node::set_orientation_listener>(
                            &extrusion_node::set_orientation_listener_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        extrusion_node::set_scale_listener>(
                            &extrusion_node::set_scale_listener_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        extrusion_node::set_spine_listener>(
                            &extrusion_node::set_spine_listener_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &extrusion_node::begin_cap_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &extrusion_node::ccw_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &extrusion_node::convex_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &extrusion_node::crease_angle_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfvec2f>(
                            &extrusion_node::cross_section_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &extrusion_node::end_cap_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfrotation>(
                            &extrusion_node::orientation_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfvec2f>(
                            &extrusion_node::scale_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &extrusion_node::solid_)));
            } else if (*interface == *++supported_interface) {
                extrusionNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfvec3f>(
                            &extrusion_node::spine_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class extrusion_node
     *
     * @brief Extrusion node instances.
     */

    /**
     * @var extrusion_node::extrusion_class
     *
     * @brief Class object for Extrusion nodes.
     */

    /**
     * @internal
     *
     * @class extrusion_node::set_cross_section_listener
     *
     * @brief set_crossSection event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  extrusion_node.
     */
    extrusion_node::set_cross_section_listener::
    set_cross_section_listener(extrusion_node & node):
        node_event_listener(node),
        event_listener_base<extrusion_node>(node),
        mfvec2f_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    extrusion_node::set_cross_section_listener::
    ~set_cross_section_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param cross_section cross_section value.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    extrusion_node::set_cross_section_listener::
    do_process_event(const mfvec2f & cross_section, double)
        throw (std::bad_alloc)
    {
        try {
            extrusion_node & extrusion =
                dynamic_cast<extrusion_node &>(this->node());
            extrusion.cross_section_ = cross_section;
            extrusion.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class extrusion_node::set_orientation_listener
     *
     * @brief set_orientation event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  extrusion_node.
     */
    extrusion_node::set_orientation_listener::
    set_orientation_listener(extrusion_node & node):
        node_event_listener(node),
        event_listener_base<extrusion_node>(node),
        mfrotation_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    extrusion_node::set_orientation_listener::
    ~set_orientation_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param orientation   orientation value.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    extrusion_node::set_orientation_listener::
    do_process_event(const mfrotation & orientation, double)
        throw (std::bad_alloc)
    {
        try {
            extrusion_node & extrusion =
                dynamic_cast<extrusion_node &>(this->node());
            extrusion.orientation_ = orientation;
            extrusion.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class extrusion_node::set_scale_listener
     *
     * @brief set_scale event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  extrusion_node.
     */
    extrusion_node::set_scale_listener::
    set_scale_listener(extrusion_node & node):
        node_event_listener(node),
        event_listener_base<extrusion_node>(node),
        mfvec2f_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    extrusion_node::set_scale_listener::
    ~set_scale_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param scale     scale value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    extrusion_node::set_scale_listener::
    do_process_event(const mfvec2f & scale, double) throw (std::bad_alloc)
    {
        try {
            extrusion_node & extrusion =
                dynamic_cast<extrusion_node &>(this->node());
            extrusion.scale_ = scale;
            extrusion.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class extrusion_node::set_spine_listener
     *
     * @brief set_spine event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  extrusion_node.
     */
    extrusion_node::set_spine_listener::
    set_spine_listener(extrusion_node & node):
        node_event_listener(node),
        event_listener_base<extrusion_node>(node),
        mfvec3f_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    extrusion_node::set_spine_listener::
    ~set_spine_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param spine     spine value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    extrusion_node::set_spine_listener::
    do_process_event(const mfvec3f & spine, double) throw (std::bad_alloc)
    {
        try {
            extrusion_node & extrusion =
                dynamic_cast<extrusion_node &>(this->node());
            extrusion.spine_ = spine;
            extrusion.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var extrusion_node::set_cross_section_listener extrusion_node::set_cross_section_listener_
     *
     * @brief set_crossSection eventIn handler.
     */

    /**
     * @var extrusion_node::set_orientation_listener extrusion_node::set_orientation_listener_
     *
     * @brief set_orientation eventIn handler.
     */

    /**
     * @var extrusion_node::set_scale_listener extrusion_node::set_scale_listener_
     *
     * @brief set_scale eventIn handler.
     */

    /**
     * @var extrusion_node::set_spine_listener extrusion_node::set_spine_listener_
     *
     * @brief set_spine eventIn handler.
     */

    /**
     * @var openvrml::sfbool extrusion_node::begin_cap_
     *
     * @brief beginCap field.
     */

    /**
     * @var openvrml::sfbool extrusion_node::ccw_
     *
     * @brief ccw field.
     */

    /**
     * @var openvrml::sfbool extrusion_node::convex_
     *
     * @brief convex field.
     */

    /**
     * @var openvrml::sffloat extrusion_node::crease_angle_
     *
     * @brief creaseAngle field.
     */

    /**
     * @var openvrml::mfvec2f extrusion_node::cross_section_
     *
     * @brief crossSection field.
     */

    /**
     * @var openvrml::sfbool extrusion_node::end_cap_
     *
     * @brief endCap field.
     */

    /**
     * @var openvrml::mfrotation extrusion_node::orientation_
     *
     * @brief orientation field.
     */

    /**
     * @var openvrml::mfvec2f extrusion_node::scale_
     *
     * @brief scale field.
     */

    /**
     * @var openvrml::sfbool extrusion_node::solid_
     *
     * @brief solid field.
     */

    /**
     * @var openvrml::mfvec3f extrusion_node::spine_
     *
     * @brief spine field.
     */

    const openvrml::vec2f extrusionDefaultCrossSection_[] =
    {
        openvrml::vec2f(1.0, 1.0),
        openvrml::vec2f(1.0, -1.0),
        openvrml::vec2f(-1.0, -1.0),
        openvrml::vec2f(-1.0, 1.0),
        openvrml::vec2f(1.0, 1.0)
    };

    const openvrml::vec2f extrusionDefaultScale_[] =
    {
        openvrml::vec2f(1.0, 1.0)
    };

    const openvrml::rotation extrusionDefaultOrientation_[] =
    {
        openvrml::rotation(0.0, 0.0, 1.0, 0.0)
    };

    const openvrml::vec3f extrusionDefaultSpine_[] =
    {
        openvrml::vec3f(0.0, 0.0, 0.0),
        openvrml::vec3f(0.0, 1.0, 0.0)
    };

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    extrusion_node::
    extrusion_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<extrusion_node>(type, scope),
        geometry_node(type, scope),
        set_cross_section_listener_(*this),
        set_orientation_listener_(*this),
        set_scale_listener_(*this),
        set_spine_listener_(*this),
        begin_cap_(true),
        ccw_(true),
        convex_(true),
        crease_angle_(0),
        cross_section_(std::vector<vec2f>(extrusionDefaultCrossSection_,
                                          extrusionDefaultCrossSection_ + 5)),
        end_cap_(true),
        orientation_(std::vector<rotation>(extrusionDefaultOrientation_,
                                           extrusionDefaultOrientation_ + 1)),
        scale_(std::vector<vec2f>(extrusionDefaultScale_,
                                  extrusionDefaultScale_ + 1)),
        solid_(true),
        spine_(std::vector<vec3f>(extrusionDefaultSpine_,
                                  extrusionDefaultSpine_ + 2))
    {}

    /**
     * @brief Destroy.
     */
    extrusion_node::~extrusion_node() throw () {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    extrusion_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        viewer::object_t obj = 0;
        if (!this->cross_section_.value().empty()
            && this->spine_.value().size() > 1) {
            unsigned int optMask = 0;
            if (this->ccw_.value())       { optMask |= viewer::mask_ccw; }
            if (this->convex_.value())    { optMask |= viewer::mask_convex; }
            if (this->solid_.value())     { optMask |= viewer::mask_solid; }
            if (this->begin_cap_.value()) { optMask |= viewer::mask_bottom; }
            if (this->end_cap_.value())   { optMask |= viewer::mask_top; }

            obj = viewer.insert_extrusion(optMask,
                                          this->spine_.value(),
                                          this->cross_section_.value(),
                                          this->orientation_.value(),
                                          this->scale_.value());
        }

        return obj;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    fog_class::fog_class(openvrml::browser & browser):
        node_class(browser),
        first(0)
    {}

    /**
     * @brief Destroy.
     */
    fog_class::~fog_class() throw ()
    {}

    /**
     * @brief Set the first Fog node in the world.
     *
     * The first Fog node in the world is used for the initial fog.
     * This method is used by fog_node::do_initialize.
     *
     * @param fog   a Fog node.
     */
    void fog_class::set_first(fog_node & fog) throw ()
    {
        this->first = &fog;
    }

    /**
     * @brief Reset the pointer to the first Fog node in the world to null.
     *
     * This function is called by <code>fog_node::do_shutdown</code>.
     */
    void fog_class::reset_first() throw ()
    {
        this->first = 0;
    }

    /**
     * @brief Check to see if the first node has been set.
     *
     * This method is used by fog_node::do_initialize.
     *
     * @return @c true if the first node has already been set; @c false
     *         otherwise.
     */
    bool fog_class::has_first() const throw ()
    {
        return this->first;
    }

    /**
     * @brief Check to see if a node is registered as the "first" node.
     *
     * @param fog   a fog_node.
     *
     * @return @c true if @p fog is the fist node; @c false otherwise.
     */
    bool fog_class::is_first(fog_node & fog) throw ()
    {
        return &fog == this->first;
    }

    /**
     * @brief Push a Fog on the top of the bound node stack.
     *
     * @param fog       the node to bind.
     * @param timestamp the current time.
     */
    void fog_class::bind(fog_node & fog,
                         const double timestamp)
        throw (std::bad_alloc)
    {
        using std::find;

        //
        // If the node is already the active node, do nothing.
        //
        if (!this->bound_nodes.empty() && &fog == this->bound_nodes.back()) {
            return;
        }

        //
        // If the node is already on the stack, remove it.
        //
        const bound_nodes_t::iterator pos =
            find(this->bound_nodes.begin(), this->bound_nodes.end(), &fog);
        if (pos != this->bound_nodes.end()) { this->bound_nodes.erase(pos); }

        //
        // Send FALSE from the currently active node's isBound.
        //
        if (!this->bound_nodes.empty()) {
            fog_node & current =
                dynamic_cast<fog_node &>(*this->bound_nodes.back());
            current.is_bound_.value(false);
            node::emit_event(current.is_bound_emitter_, timestamp);
        }

        //
        // Push the node to the top of the stack, and have it send isBound
        // TRUE.
        //
        this->bound_nodes.push_back(&fog);
        fog.is_bound_.value(true);
        node::emit_event(fog.is_bound_emitter_, timestamp);
    }

    /**
     * @brief Remove a Fog from the bound node stack.
     *
     * @param fog       the node to unbind.
     * @param timestamp the current time.
     */
    void fog_class::unbind(fog_node & fog,
                           const double timestamp) throw ()
    {
        using std::find;

        const bound_nodes_t::iterator pos = find(this->bound_nodes.begin(),
                                                 this->bound_nodes.end(),
                                                 &fog);
        if (pos != this->bound_nodes.end()) {
            fog.is_bound_.value(false);
            node::emit_event(fog.is_bound_emitter_, timestamp);

            if (pos == this->bound_nodes.end() - 1
                && this->bound_nodes.size() > 1) {
                fog_node & newActive =
                    dynamic_cast<fog_node &>(**(this->bound_nodes.end() - 2));
                newActive.is_bound_.value(true);
                node::emit_event(newActive.is_bound_emitter_, timestamp);
            }
            this->bound_nodes.erase(pos);
        }
    }

    /**
     * @brief node_class-specific initialization.
     *
     * @param initial_viewpoint the viewpoint_node that should be bound
     *                          initially.
     * @param timestamp         the current time.
     */
    void
    fog_class::
    do_initialize(openvrml::viewpoint_node *, const double timestamp) throw ()
    {
        if (this->first) {
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

    /**
     * @brief node_class-specific rendering.
     *
     * Render the active Fog node.
     *
     * @param v a viewer.
     */
    void fog_class::do_render(viewer & v) const throw ()
    {
        if (!this->bound_nodes.empty()) {
            fog_node & fog =
                dynamic_cast<fog_node &>(*this->bound_nodes.back());
            v.set_fog(fog.color_.sfcolor::value(),
                      fog.visibility_range_.sffloat::value(),
                      fog.fog_type_.sfstring::value().c_str());
        }
    }

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Fog nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by fog_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    fog_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 5> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sfbool_id,
                           "set_bind"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfstring_id,
                           "fogType"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "visibilityRange"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isBound")
        };

        typedef node_type_impl<fog_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & fogNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                fogNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        fog_node::set_bind_listener>(
                            &fog_node::set_bind_listener_)));
            } else if (*interface == *++supported_interface) {
                fogNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<fog_node>::exposedfield<sfcolor> >(
                            &fog_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<fog_node>::exposedfield<sfcolor> >(
                            &fog_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<fog_node>::exposedfield<sfcolor> >(
                            &fog_node::color_)));
            } else if (*interface == *++supported_interface) {
                fogNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<fog_node>::exposedfield<sfstring> >(
                            &fog_node::fog_type_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<fog_node>::exposedfield<sfstring> >(
                            &fog_node::fog_type_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<fog_node>::exposedfield<sfstring> >(
                            &fog_node::fog_type_)));
            } else if (*interface == *++supported_interface) {
                fogNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<fog_node>::exposedfield<sffloat> >(
                            &fog_node::visibility_range_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<fog_node>::exposedfield<sffloat> >(
                            &fog_node::visibility_range_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<fog_node>::exposedfield<sffloat> >(
                            &fog_node::visibility_range_)));
            } else if (*interface == *++supported_interface) {
                fogNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<fog_node>::sfbool_emitter>(
                            &fog_node::is_bound_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class fog_node
     *
     * @brief Fog node instances.
     */

    /**
     * @var class fog_node::fog_class
     *
     * @brief Class object for Fog nodes.
     */

    /**
     * @internal
     *
     * @class fog_node::set_bind_listener
     *
     * @brief set_bind event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  fog_node.
     */
    fog_node::set_bind_listener::
    set_bind_listener(fog_node & node):
        node_event_listener(node),
        event_listener_base<fog_node>(node),
        sfbool_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    fog_node::set_bind_listener::~set_bind_listener()
        throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param bind      bind state.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    fog_node::set_bind_listener::
    do_process_event(const sfbool & bind, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            fog_node & fog = dynamic_cast<fog_node &>(this->node());
            fog_class & node_class =
                const_cast<fog_class &>(
                    static_cast<const fog_class &>(fog.type().node_class()));
            if (bind.value()) {
                node_class.bind(fog, timestamp);
            } else {
                node_class.unbind(fog, timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var fog_node::set_bind_listener fog_node::set_bind_listener_
     *
     * @brief set_bind eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<fog_node>::exposedfield<openvrml::sfcolor> fog_node::color_
     *
     * @brief color exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<fog_node>::exposedfield<openvrml::sfstring> fog_node::fog_type_
     *
     * @brief fogType exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<fog_node>::exposedfield<openvrml::sffloat> fog_node::visibility_range_
     *
     * @brief visibilityRange exposedField.
     */

    /**
     * @var openvrml::sfbool fog_node::is_bound_
     *
     * @brief isBound eventOut value.
     */

    /**
     * @var openvrml::sfbool fog_node::is_bound_emitter_
     *
     * @brief isBound eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    fog_node::
    fog_node(const node_type & type,
             const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<fog_node>(type, scope),
        child_node(type, scope),
        set_bind_listener_(*this),
        color_(*this, openvrml::color(1.0, 1.0, 1.0)),
        fog_type_(*this, "LINEAR"),
        visibility_range_(*this, 0.0),
        is_bound_emitter_(*this, this->is_bound_)
    {}

    /**
     * @brief Destroy.
     */
    fog_node::~fog_node() throw ()
    {}

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     */
    void fog_node::do_initialize(double)
        throw ()
    {
        fog_class & nodeClass =
            const_cast<fog_class &>(
                static_cast<const fog_class &>(this->type().node_class()));
        if (!nodeClass.has_first()) { nodeClass.set_first(*this); }
    }

    /**
     * @brief Shut down.
     *
     * Calls fog_class::unbind to unbind the node if it is bound.
     *
     * @param timestamp the current time.
     */
    void fog_node::do_shutdown(const double timestamp)
        throw ()
    {
        fog_class & node_class =
            const_cast<fog_class &>(
                static_cast<const fog_class &>(this->type().node_class()));
        node_class.unbind(*this, timestamp);

        if (node_class.is_first(*this)) { node_class.reset_first(); }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    font_style_class::
    font_style_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    font_style_class::~font_style_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating FontStyle nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by font_style_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    font_style_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 9> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::field_id,
                           field_value::mfstring_id,
                           "family"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "horizontal"),
            node_interface(node_interface::field_id,
                           field_value::mfstring_id,
                           "justify"),
            node_interface(node_interface::field_id,
                           field_value::sfstring_id,
                           "language"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "leftToRight"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "size"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "spacing"),
            node_interface(node_interface::field_id,
                           field_value::sfstring_id,
                           "style"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "topToBottom")
        };

        typedef node_type_impl<font_style_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & fontStyleNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfstring>(
                            &font_style_node::family_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &font_style_node::horizontal_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfstring>(
                            &font_style_node::justify_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfstring>(
                            &font_style_node::language_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &font_style_node::leftToRight)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &font_style_node::size_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &font_style_node::spacing_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfstring>(
                            &font_style_node::style_)));
            } else if (*interface == *++supported_interface) {
                fontStyleNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &font_style_node::topToBottom)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class font_style_node
     *
     * @brief FontStyle node instances.
     */

    /**
     * @var font_style_node::font_style_class
     *
     * @brief Class object for FontStyle nodes.
     */

    /**
     * @var openvrml::mfstring font_style_node::family_
     *
     * @brief family field.
     */

    /**
     * @var openvrml::sfbool font_style_node::horizontal_
     *
     * @brief horizontal field.
     */

    /**
     * @var openvrml::mfstring font_style_node::justify_
     *
     * @brief justify field.
     */

    /**
     * @var openvrml::sfstring font_style_node::language_
     *
     * @brief language field.
     */

    /**
     * @var openvrml::sfbool font_style_node::leftToRight
     *
     * @brief leftToRight field.
     */

    /**
     * @var openvrml::sffloat font_style_node::size_
     *
     * @brief size field.
     */

    /**
     * @var openvrml::sffloat font_style_node::spacing_
     *
     * @brief spacing field.
     */

    /**
     * @var openvrml::sfstring font_style_node::style_
     *
     * @brief style field.
     */

    /**
     * @var openvrml::sfbool font_style_node::topToBottom
     *
     * @brief topToBottom field.
     */

    const std::string fontStyleInitFamily_[] = { "SERIF" };
    const std::string fontStyleInitJustify_[] = { "BEGIN", "FIRST" };

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    font_style_node::
    font_style_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<font_style_node>(type, scope),
        openvrml::font_style_node(type, scope),
        family_(std::vector<std::string>(fontStyleInitFamily_,
                                         fontStyleInitFamily_ + 1)),
        horizontal_(true),
        justify_(std::vector<std::string>(fontStyleInitJustify_,
                                          fontStyleInitJustify_ + 2)),
        leftToRight(true),
        size_(1.0),
        spacing_(1.0),
        style_("PLAIN"),
        topToBottom(true)
    {}

    /**
     * @brief Destroy.
     */
    font_style_node::~font_style_node() throw ()
    {}

    /**
     * @brief Get the list of font families.
     *
     * @return an mfstring containing the font families that may be used for
     *         this <code>font_style_node</code>.
     */
    const std::vector<std::string> &
    font_style_node::family() const throw ()
    {
        return this->family_.value();
    }

    /**
     * @brief Get the flag indicating whether the text should be horizontal or
     *        vertical.
     *
     * @return @c true if the text should be horizontal, or @c false if the
     *         text should be vertical.
     */
    bool font_style_node::horizontal() const throw ()
    {
        return this->horizontal_.value();
    }

    /**
     * @brief Get the descriptor for the text justification.
     *
     * @return a string array describing the characteristics of the text
     *         justification.
     */
    const std::vector<std::string> &
    font_style_node::justify() const throw ()
    {
        return this->justify_.value();
    }

    /**
     * @brief Get the language code.
     *
     * @return the language code.
     */
    const std::string & font_style_node::language() const
        throw ()
    {
        return this->language_.value();
    }

    /**
     * @brief Get the flag indicating whether the text should be rendered
     *      left-to-right.
     *
     * @return @c true if the text should be rendered left-to-right, or
     *         @c false if the text should be rendered right-to-left.
     */
    bool font_style_node::left_to_right() const throw ()
    {
        return this->leftToRight.value();
    }

    /**
     * @brief Get the size of the text.
     *
     * @return the size of the text.
     */
    float font_style_node::size() const throw ()
    {
        return this->size_.value();
    }

    /**
     * @brief Get the spacing for the text.
     *
     * @return the spacing for the text.
     */
    float font_style_node::spacing() const throw ()
    {
        return this->spacing_.value();
    }

    /**
     * @brief Get the style for the text.
     *
     * @return an string descriptor of the text style.
     */
    const std::string & font_style_node::style() const
        throw ()
    {
        return this->style_.value();
    }

    /**
     * @brief Get the flag indicating whether the text should be rendered
     *      top-to-bottom.
     *
     * @return @c true if the text should be rendered top-to-bottom, or
     *         @c false if the text should be rendered bottom-to-top.
     */
    bool font_style_node::top_to_bottom() const throw ()
    {
        return this->topToBottom.value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    group_class::group_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    group_class::~group_class() throw () {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Group nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by group_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    group_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 5> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "addChildren"),
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "removeChildren"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "children"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize")
        };

        typedef node_type_impl<group_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & groupNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end(); ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                groupNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        group_node::add_children_listener>(
                            &group_node::add_children_listener_)));
            } else if (*interface == *++supported_interface) {
                groupNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        group_node::remove_children_listener>(
                            &group_node::remove_children_listener_)));
            } else if (*interface == *++supported_interface) {
                groupNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        group_node::children_exposedfield>(
                            &group_node::children_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        group_node::children_exposedfield>(
                            &group_node::children_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        group_node::children_exposedfield>(
                            &group_node::children_)));
            } else if (*interface == *++supported_interface) {
                groupNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &group_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                groupNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &group_node::bbox_size_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class group_node
     *
     * @brief Represents Group node instances.
     */

    /**
     * @var group_node::group_class
     *
     * @brief Class object for Group nodes.
     */

    /**
     * @brief Construct.
     */
    group_node::
    group_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        grouping_node_base<group_node>(type, scope)
    {}

    /**
     * @brief Destroy.
     */
    group_node::~group_node() throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    image_texture_class::
    image_texture_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    image_texture_class::~image_texture_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating ImageTexture nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by image_texture_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    image_texture_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 3> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "url"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatS"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatT")
        };

        typedef node_type_impl<image_texture_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & imageTextureNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                imageTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        image_texture_node::url_exposedfield>(
                            &image_texture_node::url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        image_texture_node::url_exposedfield>(
                            &image_texture_node::url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        image_texture_node::url_exposedfield>(
                            &image_texture_node::url_)));
            } else if (*interface == *++supported_interface) {
                imageTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &image_texture_node::repeat_s_)));
            } else if (*interface == *++supported_interface) {
                imageTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &image_texture_node::repeat_t_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class image_texture_node
     *
     * @brief Represents ImageTexture node instances.
     */

    /**
     * @var class image_texture_node::image_texture_class
     *
     * @brief Class object for ImageTexture nodes.
     */

    /**
     * @internal
     *
     * @class image_texture_node::url_exposedfield
     *
     * @brief url exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param node  image_texture_node.
     */
    image_texture_node::url_exposedfield::
    url_exposedfield(image_texture_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    image_texture_node::url_exposedfield::
    url_exposedfield(const url_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    image_texture_node::url_exposedfield::
    ~url_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    image_texture_node::url_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new url_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param url       url.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    image_texture_node::url_exposedfield::
    event_side_effect(const mfstring & url, double)
        throw (std::bad_alloc)
    {
        try {
            image_texture_node & image_texture =
                dynamic_cast<image_texture_node &>(
                    this->node_event_listener::node());

            image_texture.url_.mfstring::value(url.value());
            image_texture.texture_needs_update = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var image_texture_node::url_exposedfield image_texture_node::url_
     *
     * @brief url exposedField.
     */

    /**
     * @var openvrml::image image_texture_node::image_
     *
     * @brief Image data.
     */

    /**
     * @var bool image_texture_node::texture_needs_update
     *
     * @brief Flag to indicate that image_texture_node::update_texture should
     *        be called.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope the scope to which the node belongs.
     */
    image_texture_node::
    image_texture_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_texture_node<image_texture_node>(type, scope),
        url_(*this),
        texture_needs_update(true)
    {}

    /**
     * @brief Destroy.
     */
    image_texture_node::~image_texture_node() throw ()
    {
        // delete texObject...
    }

    /**
     * @brief The image.
     *
     * @return the image.
     */
    const openvrml::image &
    image_texture_node::image() const throw ()
    {
        return this->image_;
    }

    /**
     * @brief render_texture implementation.
     *
     * @param v viewer.
     *
     * @return object identifier for the inserted texture.
     */
    openvrml::viewer::texture_object_t
    image_texture_node::do_render_texture(viewer & v)
    {
        this->update_texture();
        return v.insert_texture(this->image_,
                                this->repeat_s_.value(),
                                this->repeat_t_.value(),
                                true);
    }

    /**
     * @brief Called to lazily update texture data.
     */
    void image_texture_node::update_texture()
    {
        if (this->texture_needs_update) {
            if (!this->url_.mfstring::value().empty()) {
                using std::auto_ptr;
                auto_ptr<resource_istream> in(
                    this->scene()->get_resource(this->url_.mfstring::value()));
                auto_ptr<stream_listener>
                    listener(new image_stream_listener(this->image_,
                                                       *this,
                                                       this->mutex()));
                read_stream(in, listener);
            }
            this->texture_needs_update = false;
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    indexed_face_set_class::
    indexed_face_set_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    indexed_face_set_class::~indexed_face_set_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating IndexedFaceSet nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  indexed_face_set_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    indexed_face_set_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 18> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_colorIndex"),
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_coordIndex"),
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_normalIndex"),
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_texCoordIndex"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "coord"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "normal"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "texCoord"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "ccw"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "colorIndex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "colorPerVertex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "convex"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "coordIndex"),
            node_interface(node_interface::field_id,
                           field_value::sffloat_id,
                           "creaseAngle"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "normalIndex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "normalPerVertex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "solid"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "texCoordIndex")
        };

        typedef node_type_impl<indexed_face_set_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & indexedFaceSetNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_face_set_node::set_color_index_listener>(
                            &indexed_face_set_node::set_color_index_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_face_set_node::set_coord_index_listener>(
                            &indexed_face_set_node::set_coord_index_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_face_set_node::set_normal_index_listener>(
                            &indexed_face_set_node::set_normal_index_listener_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_face_set_node::set_tex_coord_index_listener>(
                            &indexed_face_set_node::set_tex_coord_index_listener_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::color_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::coord_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::coord_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::coord_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::normal_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::normal_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::normal_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::tex_coord_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::tex_coord_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_face_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_face_set_node::tex_coord_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_face_set_node::ccw_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_face_set_node::color_index_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_face_set_node::color_per_vertex_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_face_set_node::convex_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_face_set_node::coord_index_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &indexed_face_set_node::crease_angle_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_face_set_node::normal_index_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_face_set_node::normal_per_vertex_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_face_set_node::solid_)));
            } else if (*interface == *++supported_interface) {
                indexedFaceSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_face_set_node::tex_coord_index_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class indexed_face_set_node
     *
     * @brief Represents IndexedFaceSet node instances.
     */

    /**
     * @internal
     *
     * @class indexed_face_set_node::set_normal_index_listener
     *
     * @brief set_normalIndex event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  indexed_face_set_node.
     */
    indexed_face_set_node::set_normal_index_listener::
    set_normal_index_listener(indexed_face_set_node & node):
        node_event_listener(node),
        event_listener_base<indexed_face_set_node>(node),
        mfint32_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    indexed_face_set_node::set_normal_index_listener::
    ~set_normal_index_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param normal_index normalIndex.
     * @param timestamp   the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    indexed_face_set_node::set_normal_index_listener::
    do_process_event(const mfint32 & normal_index, double)
        throw (std::bad_alloc)
    {
        try {
            indexed_face_set_node & indexed_face_set =
                dynamic_cast<indexed_face_set_node &>(this->node());

            indexed_face_set.normal_index_ = normal_index;
            indexed_face_set.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class indexed_face_set_node::set_tex_coord_index_listener
     *
     * @brief set_coordIndex event handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  indexed_face_set_node.
     */
    indexed_face_set_node::set_tex_coord_index_listener::
    set_tex_coord_index_listener(indexed_face_set_node & node):
        node_event_listener(node),
        event_listener_base<indexed_face_set_node>(node),
        mfint32_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    indexed_face_set_node::set_tex_coord_index_listener::
    ~set_tex_coord_index_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param tex_coord_index   texCoordIndex.
     * @param timestamp         the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    indexed_face_set_node::set_tex_coord_index_listener::
    do_process_event(const mfint32 & tex_coord_index, double)
        throw (std::bad_alloc)
    {
        try {
            indexed_face_set_node & indexed_face_set =
                dynamic_cast<indexed_face_set_node &>(this->node());

            indexed_face_set.tex_coord_index_ = tex_coord_index;
            indexed_face_set.node::modified(true);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var indexed_face_set_node::indexed_face_set_class
     *
     * @brief Class object for IndexedFaceSet nodes.
     */

    /**
     * @var indexed_face_set_node::set_normal_index_listener indexed_face_set_node::set_normal_index_listener_
     *
     * @brief set_normalIndex eventIn handler.
     */

    /**
     * @var indexed_face_set_node::set_tex_coord_index_listener indexed_face_set_node::set_tex_coord_index_listener_
     *
     * @brief set_texCoordIndex eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<indexed_face_set_node>::exposedfield<openvrml::sfnode> indexed_face_set_node::normal_
     *
     * @brief normal exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<indexed_face_set_node>::exposedfield<openvrml::sfnode> indexed_face_set_node::tex_coord_
     *
     * @brief texCoord exposedField.
     */

    /**
     * @var openvrml::sfbool indexed_face_set_node::ccw_
     *
     * @brief ccw field.
     */

    /**
     * @var openvrml::sfbool indexed_face_set_node::convex_
     *
     * @brief convex field.
     */

    /**
     * @var openvrml::sffloat indexed_face_set_node::crease_angle_
     *
     * @brief creaseAngle field.
     */

    /**
     * @var openvrml::mfint32 indexed_face_set_node::normal_index_
     *
     * @brief set_normalIndex eventIn.
     */

    /**
     * @var openvrml::sfbool indexed_face_set_node::normal_per_vertex_
     *
     * @brief normalPerVertex field.
     */

    /**
     * @var openvrml::sfbool indexed_face_set_node::solid_
     *
     * @brief solid field.
     */

    /**
     * @var openvrml::mfint32 indexed_face_set_node::tex_coord_index_
     *
     * @brief set_texCoordIndex eventIn.
     */

    /**
     * @var bounding_sphere indexed_face_set_node::bsphere
     *
     * @brief Bounding volume.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    indexed_face_set_node::
    indexed_face_set_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_indexed_set_node<indexed_face_set_node>(type, scope),
        set_normal_index_listener_(*this),
        set_tex_coord_index_listener_(*this),
        normal_(*this),
        tex_coord_(*this),
        ccw_(true),
        convex_(true),
        crease_angle_(0.0),
        normal_per_vertex_(true),
        solid_(true)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    indexed_face_set_node::~indexed_face_set_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool indexed_face_set_node::modified() const
    {
        return this->node::modified()
            || (this->color_.sfnode::value()
                && this->color_.sfnode::value()->modified())
            || (this->coord_.sfnode::value()
                && this->coord_.sfnode::value()->modified())
            || (this->normal_.sfnode::value()
                && this->normal_.sfnode::value()->modified())
            || (this->tex_coord_.sfnode::value()
                && this->tex_coord_.sfnode::value()->modified());
    }

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     *
     * @todo stripify, crease angle, generate normals ...
     */
    openvrml::viewer::object_t
    indexed_face_set_node::
    do_render_geometry(openvrml::viewer & viewer,
                       const rendering_context context)
    {
        using std::vector;

        if (context.draw_bounding_spheres) {
            assert(dynamic_cast<const bounding_sphere *>(
                       &this->bounding_volume()));
            const bounding_sphere & bs =
                static_cast<const bounding_sphere &>(this->bounding_volume());
            viewer.draw_bounding_sphere(bs,
                                        static_cast<bounding_volume::intersection>(4));
        }

        openvrml::coordinate_node * const coordinateNode =
            node_cast<openvrml::coordinate_node *>(
                this->coord_.sfnode::value().get());
        const vector<vec3f> & coord = coordinateNode
            ? coordinateNode->point()
            : vector<vec3f>();

        openvrml::color_node * const colorNode =
            node_cast<openvrml::color_node *>(
                this->color_.sfnode::value().get());
        const vector<openvrml::color> & color = colorNode
            ? colorNode->color()
            : vector<openvrml::color>();

        openvrml::normal_node * const normalNode =
            node_cast<openvrml::normal_node *>(
                this->normal_.sfnode::value().get());
        const vector<vec3f> & normal = normalNode
            ? normalNode->vector()
            : vector<vec3f>();

        openvrml::texture_coordinate_node * const texCoordNode =
            node_cast<openvrml::texture_coordinate_node *>(
                this->tex_coord_.sfnode::value().get());
        const vector<vec2f> & texCoord = texCoordNode
            ? texCoordNode->point()
            : vector<vec2f>();

        unsigned int optMask = 0;
        if (this->ccw_.value()) {
            optMask |= viewer::mask_ccw;
        }
        if (this->convex_.value()) {
            optMask |= viewer::mask_convex;
        }
        if (this->solid_.value()) {
            optMask |= viewer::mask_solid;
        }
        if (this->color_per_vertex_.value()) {
            optMask |= viewer::mask_color_per_vertex;
        }
        if (this->normal_per_vertex_.value()) {
            optMask |= viewer::mask_normal_per_vertex;
        }

        const viewer::object_t obj =
            viewer.insert_shell(optMask,
                                coord, this->coord_index_.value(),
                                color, this->color_index_.value(),
                                normal, this->normal_index_.value(),
                                texCoord, this->tex_coord_index_.value());

        if (colorNode) { colorNode->modified(false); }
        if (coordinateNode) { coordinateNode->modified(false); }
        if (normalNode) { normalNode->modified(false); }
        if (texCoordNode) { texCoordNode->modified(false); }

        return obj;
    }

    /**
     * @brief Recalculate the bounding volume.
     */
    void indexed_face_set_node::recalc_bsphere()
    {
        // take the bvolume of all the points. technically, we should figure
        // out just which points are used by the index and just use those,
        // but for a first pass this is fine (also: if we do it this way
        // then we don't have to update the bvolume when the index
        // changes). motto: always do it the simple way first...
        //
        openvrml::coordinate_node * const coordinateNode =
            node_cast<openvrml::coordinate_node *>(
                this->coord_.sfnode::value().get());
        if (coordinateNode) {
            const std::vector<vec3f> & coord = coordinateNode->point();
            this->bsphere = bounding_sphere();
            this->bsphere.enclose(coord);
        }
        this->bounding_volume_dirty(false);
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    indexed_face_set_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<indexed_face_set_node *>(this)->recalc_bsphere();
        }
        return this->bsphere;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    indexed_line_set_class::
    indexed_line_set_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    indexed_line_set_class::~indexed_line_set_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating IndexedLineSet nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  indexed_line_set_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    indexed_line_set_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 7> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_colorIndex"),
            node_interface(node_interface::eventin_id,
                           field_value::mfint32_id,
                           "set_coordIndex"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "coord"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "colorIndex"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "colorPerVertex"),
            node_interface(node_interface::field_id,
                           field_value::mfint32_id,
                           "coordIndex")
        };

        typedef node_type_impl<indexed_line_set_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & indexedLineSetNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_line_set_node::set_color_index_listener>(
                            &indexed_line_set_node::set_color_index_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        indexed_line_set_node::set_coord_index_listener>(
                            &indexed_line_set_node::set_coord_index_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::color_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::coord_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::coord_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<indexed_line_set_node>::
                        exposedfield<sfnode> >(
                            &indexed_line_set_node::coord_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_line_set_node::color_index_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &indexed_line_set_node::color_per_vertex_)));
            } else if (*interface == *++supported_interface) {
                indexedLineSetNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfint32>(
                            &indexed_line_set_node::coord_index_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class indexed_line_set_node
     *
     * @brief Represents IndexedLineSet node instances.
     */

    /**
     * @var indexed_line_set_node::indexed_line_set_class
     *
     * @brief Class object for IndexedLineSet nodes.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope the scope to which the node belongs.
     */
    indexed_line_set_node::
    indexed_line_set_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_indexed_set_node<indexed_line_set_node>(type, scope)
    {}

    /**
     * @brief Destroy.
     */
    indexed_line_set_node::~indexed_line_set_node() throw ()
    {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     *
     * @todo colors
     */
    openvrml::viewer::object_t
    indexed_line_set_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        using std::vector;

        openvrml::coordinate_node * const coordinateNode =
            node_cast<openvrml::coordinate_node *>(
                this->coord_.sfnode::value().get());
        const vector<vec3f> & coord = coordinateNode
            ? coordinateNode->point()
            : vector<vec3f>();

        openvrml::color_node * const colorNode =
            node_cast<openvrml::color_node *>(
                this->color_.sfnode::value().get());
        const vector<openvrml::color> & color = colorNode
            ? colorNode->color()
            : vector<openvrml::color>();

        viewer::object_t obj =
            viewer.insert_line_set(coord, this->coord_index_.value(),
                                   this->color_per_vertex_.value(),
                                   color, this->color_index_.value());

        if (colorNode) { colorNode->modified(false); }
        if (coordinateNode) { coordinateNode->modified(false); }

        return obj;
    }

    /**
     * @brief Indicate that line sets should be drawn with the emissive color.
     *
     * @return @c true.
     */
    bool indexed_line_set_node::do_emissive() const throw ()
    {
        return true;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    inline_class::inline_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    inline_class::~inline_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Inline nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by inline_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    inline_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 3> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "url"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize")
        };

        typedef node_type_impl<inline_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & inlineNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                inlineNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<inline_node>::exposedfield<mfstring> >(
                            &inline_node::url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<inline_node>::exposedfield<mfstring> >(
                            &inline_node::url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<inline_node>::exposedfield<mfstring> >(
                            &inline_node::url_)));
            } else if (*interface == *++supported_interface) {
                inlineNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &inline_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                inlineNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &inline_node::bbox_size_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class inline_node
     *
     * @brief Represents Inline node instances.
     */

    /**
     * @var inline_node::inline_class
     *
     * @brief Class object for Inline nodes.
     */

    /**
     * @var openvrml::sfvec3f inline_node::bbox_center_
     *
     * @brief bboxCenter field.
     */

    /**
     * @var openvrml::sfvec3f inline_node::bbox_size_
     *
     * @brief bboxSize field.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<inline_node>::exposedfield<openvrml::mfstring> inline_node::url_
     *
     * @brief url exposedField.
     */

    /**
     * @var openvrml::scene * inline_node::inlineScene
     *
     * @brief The contained scene.
     */

    /**
     * @var bool inline_node::hasLoaded
     *
     * @brief Flag to indicate whether the scene has been loaded.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope the scope to which the node belongs.
     */
    inline_node::
    inline_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<inline_node>(type, scope),
        grouping_node(type, scope),
        url_(*this),
        inlineScene(0),
        hasLoaded(false)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    inline_node::~inline_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * Render each of the children.
     *
     * @param viewer    a Viewer.
     * @param context   a rendering context.
     */
    void
    inline_node::
    do_render_child(openvrml::viewer & viewer,
                    const rendering_context context)
    {
        this->load();
        if (this->inlineScene) { this->inlineScene->render(viewer, context); }
    }

    /**
     * @brief Get the children in the scene graph.
     *
     * @return the child nodes in the scene graph.
     */
    const std::vector<boost::intrusive_ptr<openvrml::node> > &
    inline_node::do_children() const throw ()
    {
        static const std::vector<boost::intrusive_ptr<openvrml::node> > empty;
        return this->inlineScene
            ? this->inlineScene->nodes()
            : empty;
    }

    /**
     * @brief Load the children from the URL.
     */
    void inline_node::load()
    {
        class inline_scene : public openvrml::scene {
        public:
            inline_scene(openvrml::browser & b, openvrml::scene * parent):
                openvrml::scene(b, parent)
                {}

        private:
            virtual void scene_loaded()
                {
                    this->initialize(openvrml::browser::current_time());
                }
        };

        //
        // XXX Need to check whether Url has been modified.
        //
        if (this->hasLoaded) { return; }

        this->hasLoaded = true; // although perhaps not successfully
        this->bounding_volume_dirty(true);

        assert(this->scene());
        this->inlineScene = new inline_scene(this->scene()->browser(),
                                             this->scene());
        this->inlineScene->load(this->url_.mfstring::value());
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    lod_class::lod_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    lod_class::~lod_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating LOD nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by lod_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    lod_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 3> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "level"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "center"),
            node_interface(node_interface::field_id,
                           field_value::mffloat_id,
                           "range")
        };

        typedef node_type_impl<lod_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & lodNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                lodNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<lod_node>::exposedfield<mfnode> >(
                            &lod_node::level_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<lod_node>::exposedfield<mfnode> >(
                            &lod_node::level_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<lod_node>::exposedfield<mfnode> >(
                            &lod_node::level_)));
            } else if (*interface == *++supported_interface) {
                lodNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &lod_node::center_)));
            } else if (*interface == *++supported_interface) {
                lodNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mffloat>(
                            &lod_node::range_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class lod_node
     *
     * @brief Represents LOD node instances.
     */

    /**
     * @var lod_node::lod_class
     *
     * @brief Class object for LOD nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<lod_node>::exposedfield<openvrml::mfnode> lod_node::level_
     *
     * @brief level exposedField.
     */

    /**
     * @var openvrml::sfvec3f lod_node::center_
     *
     * @brief center field.
     */

    /**
     * @var openvrml::mffloat lod_node::range_
     *
     * @brief range field.
     */

    /**
     * @var openvrml::mfnode lod_node::children_
     *
     * @brief Caches the active level for fast access by lod_node::children.
     */

    /**
     * @var openvrml::bounding_sphere lod_node::bsphere
     *
     * @brief Cached copy of the bounding_sphere enclosing this node's
     *        children.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope the scope to which the node belongs.
     */
    lod_node::
    lod_node(const node_type & type,
             const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<lod_node>(type, scope),
        grouping_node(type, scope),
        level_(*this),
        children_(1)
    {
        this->bounding_volume_dirty(true); // lazy calc of bvolume
    }

    /**
     * @brief Destroy.
     */
    lod_node::~lod_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *         @c false otherwise.
     */
    bool lod_node::modified() const
    {
        if (this->node::modified()) { return true; }

        // This should really check which range is being rendered...
        for (size_t i = 0; i < this->level_.mfnode::value().size(); ++i) {
            if (this->level_.mfnode::value()[i]->modified()) { return true; }
        }
        return false;
    }

    /**
     * @brief Render the node.
     *
     * Render one of the children.
     *
     * @param viewer    a Viewer.
     * @param context   a rendering context.
     */
    void
    lod_node::
    do_render_child(openvrml::viewer & viewer,
                    const rendering_context context)
    {
        this->node::modified(false);
        if (this->level_.mfnode::value().empty()) { return; }

        float x, y, z;

        mat4f MV = context.matrix();
        MV = MV.inverse();
        x = MV[3][0]; y = MV[3][1]; z = MV[3][2];
        float dx = x - this->center_.value().x();
        float dy = y - this->center_.value().y();
        float dz = z - this->center_.value().z();
        float d2 = dx * dx + dy * dy + dz * dz;

        size_t i;
        for (i = 0; i < this->range_.value().size(); ++i) {
            if (d2 < this->range_.value()[i] * this->range_.value()[i]) {
                break;
            }
        }

        // Should choose an "optimal" level...
        if (this->range_.value().empty()) {
            i = this->level_.mfnode::value().size() - 1;
        }

        // Not enough levels...
        if (i >= this->level_.mfnode::value().size()) {
            i = this->level_.mfnode::value().size() - 1;
        }

        child_node * const child =
            node_cast<child_node *>(this->level_.mfnode::value()[i].get());
        if (child) { child->render_child(viewer, context); }

        // Don't re-render on their accounts
        for (i = 0; i < this->level_.mfnode::value().size(); ++i) {
            this->level_.mfnode::value()[i]->modified(false);
        }
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    lod_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<lod_node *>(this)->recalc_bsphere();
        }
        return this->bsphere;
    }

    /**
     * @brief Get the children in the scene graph.
     *
     * @return the child nodes in the scene graph.
     */
    const std::vector<boost::intrusive_ptr<openvrml::node> > &
    lod_node::do_children() const throw ()
    {
        return this->children_.value();
    }

    /**
     * @brief Recalculate the bounding volume.
     */
    void lod_node::recalc_bsphere()
    {
        this->bsphere = bounding_sphere();

        // let's say our bsphere is the union of the bspheres of all the
        // levels. we could have said it was just the bsphere of the current
        // level, but the current level depends on the viewer position, and
        // we'd like to make the calculation idependent of that. we could do
        // some sort of trick where we reset the bsphere during render, but
        // that seems like overkill unless this simpler method proves to be
        // a bottleneck.
        //
        // hmm: just thought of a problem: one of the uses of the lod is to
        // switch in delayed-load inlines. this would necessarily switch
        // them in all at once. live with it for now.
        //
        for (size_t i = 0; i < this->level_.mfnode::value().size(); i++) {
            const boost::intrusive_ptr<node> & node = this->level_.mfnode::value()[i];
            bounded_volume_node * bounded_volume =
                node_cast<bounded_volume_node *>(node.get());
            if (bounded_volume) {
                const openvrml::bounding_volume & ci_bv =
                    bounded_volume->bounding_volume();
                this->bsphere.extend(ci_bv);
            }
        }
        this->bounding_volume_dirty(false);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    material_class::
    material_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    material_class::~material_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Material nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by material_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    material_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 6> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "ambientIntensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "diffuseColor"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "emissiveColor"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "shininess"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "specularColor"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "transparency")
        };

        typedef node_type_impl<material_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & materialNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::ambient_intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::ambient_intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::ambient_intensity_)));
            } else if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::diffuse_color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::diffuse_color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::diffuse_color_)));
            } else if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::emissive_color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::emissive_color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::emissive_color_)));
            } else if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::shininess_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::shininess_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::shininess_)));
            } else if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::specular_color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::specular_color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sfcolor> >(
                            &material_node::specular_color_)));
            } else if (*interface == *++supported_interface) {
                materialNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::transparency_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::transparency_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<material_node>::exposedfield<sffloat> >(
                            &material_node::transparency_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class material_node
     *
     * @brief Material node instances.
     */

    /**
     * @var material_node::material_class
     *
     * @brief Class object for Material nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sffloat> material_node::ambient_intensity_
     *
     * @brief ambientIntensity exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sfcolor> material_node::diffuse_color_
     *
     * @brief diffuseColor exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sfcolor> material_node::emissive_color_
     *
     * @brief emissiveColor exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sffloat> material_node::shininess_
     *
     * @brief shininess exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sfcolor> material_node::specular_color_
     *
     * @brief specularColor exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<material_node>::exposedfield<openvrml::sffloat> material_node::transparency_
     *
     * @brief transparency exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope the scope to which the node belongs.
     */
    material_node::
    material_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<material_node>(type, scope),
        openvrml::material_node(type, scope),
        ambient_intensity_(*this, 0.2f),
        diffuse_color_(*this, color(0.8f, 0.8f, 0.8f)),
        emissive_color_(*this, color(0.0, 0.0, 0.0)),
        shininess_(*this, 0.2f),
        specular_color_(*this, color(0.0, 0.0, 0.0)),
        transparency_(*this, 0.0)
    {}

    /**
     * @brief Destroy.
     */
    material_node::~material_node() throw ()
    {}

    /**
     * @brief Get the ambient intensity.
     *
     * @return the ambient intensity.
     */
    float material_node::ambient_intensity() const throw ()
    {
        return this->ambient_intensity_.sffloat::value();
    }

    /**
     * @brief Get the diffuse color.
     *
     * @return the diffuse color.
     */
    const openvrml::color &
    material_node::diffuse_color() const throw ()
    {
        return this->diffuse_color_.sfcolor::value();
    }

    /**
     * @brief Get the emissive color.
     *
     * @return the emissive color.
     */
    const openvrml::color &
    material_node::emissive_color() const throw ()
    {
        return this->emissive_color_.sfcolor::value();
    }

    /**
     * @brief Get the shininess.
     *
     * @return the shininess.
     */
    float material_node::shininess() const throw ()
    {
        return this->shininess_.sffloat::value();
    }

    /**
     * @brief Get the specular color.
     *
     * @return the specular color.
     */
    const openvrml::color &
    material_node::specular_color() const throw ()
    {
        return this->specular_color_.sfcolor::value();
    }

    /**
     * @brief Get the transparency.
     *
     * @return the transparency.
     */
    float material_node::transparency() const throw ()
    {
        return this->transparency_.sffloat::value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    movie_texture_class::
    movie_texture_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    movie_texture_class::~movie_texture_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating MovieTexture nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by movie_texture_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    movie_texture_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 9> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "loop"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "speed"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "startTime"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "stopTime"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "url"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatS"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatT"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "duration_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive")
        };

        typedef node_type_impl<movie_texture_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & movieTextureNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                movieTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sfbool> >(
                            &movie_texture_node::loop_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sfbool> >(
                            &movie_texture_node::loop_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sfbool> >(
                            &movie_texture_node::loop_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        movie_texture_node::set_speed_listener >(
                            &movie_texture_node::set_speed_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &movie_texture_node::speed_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::sffloat_emitter>(
                            &movie_texture_node::speed_changed_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::start_time_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::start_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::start_time_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::stop_time_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::stop_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::exposedfield<sftime> >(
                            &movie_texture_node::stop_time_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<movie_texture_node>::
                        exposedfield<mfstring> >(&movie_texture_node::url_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<movie_texture_node>::
                        exposedfield<mfstring> >(
                            &movie_texture_node::url_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::
                        exposedfield<mfstring> >(&movie_texture_node::url_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &movie_texture_node::repeat_s_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &movie_texture_node::repeat_t_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::sftime_emitter>(
                            &movie_texture_node::duration_changed_)));
            } else if (*interface == *++supported_interface) {
                movieTextureNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<movie_texture_node>::sfbool_emitter>(
                            &movie_texture_node::is_active_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class movie_texture_node
     *
     * @brief MovieTexture node instances.
     */

    /**
     * @var class movie_texture_node::movie_texture_class
     *
     * @brief Class object for MovieTexture nodes.
     */

    /**
     * @internal
     *
     * @class movie_texture_node::set_speed_listener
     *
     * @brief set_speed eventIn handler.
     *
     * Unlike most exposedFields which are implemented either with an instance
     * of the exposedfield template or a class derived from it, MovieTexture's
     * speed exposedField is implemented using the listener and emitter
     * primitives. This is because unlike most exposedFields, changes to the
     * speed field (that is, set_speed events) are ignored if the node is not
     * active.
     */

    /**
     * @brief Constructor.
     *
     * @param node  movie_texture_node.
     */
    movie_texture_node::set_speed_listener::
    set_speed_listener(movie_texture_node & node):
        node_event_listener(node),
        event_listener_base<movie_texture_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    movie_texture_node::set_speed_listener::
    ~set_speed_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param speed     speed value.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    movie_texture_node::set_speed_listener::
    do_process_event(const sffloat & speed, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            movie_texture_node & node =
                dynamic_cast<movie_texture_node &>(this->node());

            //
            // set_speed is ignored if the MovieTexture is active.
            //
            if (!node.active_.value()) {
                node.speed_ = speed;
                node.node::modified(true);
                node::emit_event(node.speed_changed_, timestamp);
            }
        } catch (std::bad_alloc & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var openvrml::node_impl_util::abstract_node<movie_texture_node>::exposedfield<openvrml::sfbool> movie_texture_node::loop_
     *
     * @brief loop exposedField.
     */

    /**
     * @var movie_texture_node::set_speed_listener movie_texture_node::set_speed_
     *
     * @brief set_speed event handler for the speed exposedField.
     */

    /**
     * @var openvrml::sffloat movie_texture_node::speed_
     *
     * @brief Value for speed exposedField.
     */

    /**
     * @var openvrml::sffloat_emitter movie_texture_node::speed_changed_
     *
     * @brief speed_changed event emitter for the speed exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<movie_texture_node>::exposedfield<openvrml::sftime> movie_texture_node::start_time_
     *
     * @brief startTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<movie_texture_node>::exposedfield<openvrml::sftime> movie_texture_node::stop_time_
     *
     * @brief stopTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<movie_texture_node>::exposedfield<openvrml::mfstring> movie_texture_node::url_
     *
     * @brief url exposedField.
     */

    /**
     * @var openvrml::sftime movie_texture_node::duration_
     *
     * @brief duration value.
     */

    /**
     * @var openvrml::sftime_emitter movie_texture_node::duration_changed_
     *
     * @brief duration_changed eventOut
     */

    /**
     * @var openvrml::sfbool movie_texture_node::active_
     *
     * @brief active state.
     */

    /**
     * @var openvrml::sfbool_emitter movie_texture_node::is_active_
     *
     * @brief isActive eventOut.
     */

    /**
     * @var openvrml::image movie_texture_node::image_
     *
     * @brief Frame data.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    movie_texture_node::
    movie_texture_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_texture_node<movie_texture_node>(type, scope),
        time_dependent_node(type, scope),
        loop_(*this, false),
        set_speed_(*this),
        speed_(1.0),
        speed_changed_(*this, this->speed_),
        start_time_(*this),
        stop_time_(*this),
        url_(*this),
        duration_changed_(*this, this->duration_),
        is_active_(*this, this->active_)
    {}

    /**
     * @brief Destroy.
     */
    movie_texture_node::~movie_texture_node() throw ()
    {}

    /**
     * @brief Update the node for the current timestamp.
     *
     * @param time  the current time.
     */
    void movie_texture_node::do_update(double /* time */)
    {
# if 0
        if (this->modified()) {
            if (this->img_) {
                const char * imageUrl = this->img_->url();
                size_t imageLen = strlen(imageUrl);
                size_t i, nUrls = this->url_.mfstring::value.size();
                for (i = 0; i < nUrls; ++i) {
                    size_t len = this->url_.mfstring::value[i].length();

                    if (this->url_.mfstring::value[i] == imageUrl
                        || ((imageLen > len)
                            && (this->url_.mfstring::value[i]
                                == (imageUrl + imageLen - len)))) {
                        break;
                    }
                }

                // if (d_image->url() not in d_url list) ...
                if (i == nUrls) {
                    delete this->img_;
                    this->img_ = 0;
                }
            }
        }

        // Load the movie if needed (should check startTime...)
        if (!this->img_ && !this->url_.mfstring::value.empty()) {
            doc2 baseDoc(this->scene()->url());
            this->img_ = new img;
            if (!this->img_->try_urls(this->url_.mfstring::value, &baseDoc)) {
                std::cerr << "Error: couldn't read MovieTexture from URL "
                          << this->url_ << std::endl;
            }

            const size_t nFrames = this->img_->nframes();
            this->duration_.value = (nFrames >= 0)
                ? double(nFrames)
                : -1.0;
            node::emit_event(this->duration_changed_, time);
            this->frame = int((this->speed_.value >= 0)
                              ? 0
                              : nFrames - 1);
            // Set the last frame equal to the start time.
            // This is needed to properly handle the case where the startTime
            // and stopTime are set at runtime to the same value (spec says
            // that a single loop should occur in this case...)
            this->lastFrameTime = this->start_time_.sftime::value;
        }

        // No pictures to show
        if (!this->img_ || this->img_->nframes() == 0) { return; }

        // See section 4.6.9 of the VRML97 spec for a detailed explanation
        // of the logic here.
        if (!this->active_.value) {
            if (time >= this->start_time_.sftime::value) {
                if (time >= this->stop_time_.sftime::value) {
                    if (this->start_time_.sftime::value
                        >= this->stop_time_.sftime::value) {
                        if (this->loop_.sfbool::value) {
                            this->active_.value = true;
                            node::emit_event(this->is_active_, time);
                            this->lastFrameTime = time;
                            this->frame = int((this->speed_.value >= 0)
                                              ? 0
                                              : this->img_->nframes() - 1);
                            this->modified(true);
                        } else if (this->start_time_.sftime::value
                                   > this->lastFrameTime) {
                            this->active_.value = true;
                            node::emit_event(this->is_active_, time);
                            this->lastFrameTime = time;
                            this->frame = int((this->speed_.value >= 0)
                                              ? 0
                                              : this->img_->nframes() - 1);
                            this->modified(true);
                        }
                    }
                } else if (this->stop_time_.sftime::value > time) {
                    this->active_.value = true;
                    node::emit_event(this->is_active_, time);
                    this->lastFrameTime = time;
                    this->frame = int((this->speed_.value >= 0)
                                      ? 0
                                      : this->img_->nframes() - 1);
                    this->modified(true);
                }
            }
        }
        // Check whether stopTime has passed
        else if (this->active_.value
                 && ((this->stop_time_.sftime::value
                      > this->start_time_.sftime::value
                      && this->stop_time_.sftime::value <= time))
                 || ((this->frame < 0) && !this->loop_.sfbool::value)) {
            this->active_.value = false;
            node::emit_event(this->is_active_, time);
            this->modified(true);
        } else if (this->frame < 0 && this->loop_.sfbool::value) {
            // Reset frame to 0 to begin loop again.
            this->frame = 0;
        }

        // Check whether the frame should be advanced
        else if (this->active_.value
                 && this->lastFrameTime + fabs(1 / this->speed_.value) <= time) {
            this->frame = (this->speed_.value >= 0)
                ? int(time - this->start_time_.sftime::value)
                % int(this->duration_.value / this->speed_.value)
                : -(int(time - this->start_time_.sftime::value)
                    % int(fabs(this->duration_.value / this->speed_.value)));
            assert(this->frame >= 0);

            this->lastFrameTime = time;
            this->modified(true);
        }

        const size_t frame_bytes =
            this->img_->w() * this->img_->h() * this->img_->nc();
        this->image_ =
            openvrml::image(this->img_->w(),
                            this->img_->h(),
                            this->img_->nc(),
                            this->img_->pixels(this->frame),
                            this->img_->pixels(this->frame) + frame_bytes);

        // Tell the scene when the next update is needed.
        if (this->active_.value) {
            double d = this->lastFrameTime + fabs(1 / this->speed_.value) - time;
            this->type().node_class().browser().delta(0.9 * d);
        }
# endif
    }

    /**
     * @brief The image.
     *
     * @return the image.
     */
    const openvrml::image &
    movie_texture_node::image() const throw ()
    {
        return this->image_;
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    movie_texture_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_time_dependent(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    movie_texture_node::do_shutdown(double)
        throw ()
    {
        assert(this->scene());
        this->scene()->browser().remove_time_dependent(*this);
    }

    /**
     * @brief render_texture implementation.
     *
     * @param v viewer.
     *
     * @return object identifier for the inserted texture.
     */
    openvrml::viewer::texture_object_t
    movie_texture_node::do_render_texture(viewer & /* v */)
    {
# if 0
        if (!this->img_ || this->frame < 0) { return 0; }

        viewer::texture_object_t texture_object = 0;

        if (!this->img_->pixels(this->frame)) {
            this->frame = -1;
        } else {
            texture_object = v.insert_texture(this->image_,
                                              this->repeat_s_.value,
                                              this->repeat_t_.value,
                                              !this->active_.value);
        }

        this->lastFrame = this->frame;
        return texture_object;
# endif
        return 0;
    }


    /**
     * @typedef navigation_info_class::bound_nodes_t
     *
     * @brief A bound NavigationInfo node stack.
     */

    /**
     * @var navigation_info_node * navigation_info_class::first
     *
     * @brief The first NavigationInfo node in the initial scene graph.
     */

    /**
     * @var navigation_info_class::bound_nodes_t navigation_info_class::bound_nodes
     *
     * @brief The bound NavigationInfo node stack.
     */

    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    navigation_info_class::
    navigation_info_class(openvrml::browser & browser):
        node_class(browser),
        first(0)
    {}

    /**
     * @brief Destroy.
     */
    navigation_info_class::~navigation_info_class() throw ()
    {}

    /**
     * @brief Set the first NavigationInfo node in the world.
     *
     * The first NavigationInfo node in the world is used as the initially
     * active NavigationInfo. This method is used by
     * <code>navigation_info_node::do_initialize</code>.
     *
     * @param nav_info    a NavigationInfo node.
     */
    void
    navigation_info_class::
    set_first(navigation_info_node & nav_info) throw ()
    {
        this->first = &nav_info;
    }

    /**
     * @brief Reset the pointer to the first NavigationInfo node in the world
     *        to null.
     *
     * This function is called by
     * <code>navigation_info_node::do_shutdown</code>.
     */
    void navigation_info_class::reset_first() throw ()
    {
        this->first = 0;
    }

    /**
     * @brief Check to see if the first node has been set.
     *
     * This method is used by navigation_info_node::do_initialize.
     *
     * @return @c true if the first node has already been set; @c false
     *         otherwise.
     */
    bool navigation_info_class::has_first() const throw ()
    {
        return this->first;
    }

    /**
     * @brief Check to see if a node is registered as the "first" node.
     *
     * @param nav_info  a navigation_info_node.
     *
     * @return @c true if @p nav_info is the fist node; @c false otherwise.
     */
    bool
    navigation_info_class::
    is_first(navigation_info_node & nav_info) throw ()
    {
        return &nav_info == this->first;
    }

    /**
     * @brief Push a navigation_info_node on the top of the bound node stack.
     *
     * @param nav_info    the node to bind.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    navigation_info_class::
    bind(navigation_info_node & nav_info, const double timestamp)
        throw (std::bad_alloc)
    {
        using std::find;

        //
        // If the node is already the active node, do nothing.
        //
        if (!this->bound_nodes.empty()
            && &nav_info == this->bound_nodes.back())
        {
            return;
        }

        //
        // If the node is already on the stack, remove it.
        //
        const bound_nodes_t::iterator pos = find(this->bound_nodes.begin(),
                                                 this->bound_nodes.end(),
                                                 &nav_info);
        if (pos != this->bound_nodes.end()) { this->bound_nodes.erase(pos); }

        //
        // Send FALSE from the currently active node's isBound.
        //
        if (!this->bound_nodes.empty()) {
            navigation_info_node & current =
                dynamic_cast<navigation_info_node &>(
                    *this->bound_nodes.back());
            current.is_bound_.value(false);
            node::emit_event(current.is_bound_emitter_, timestamp);
        }

        //
        // Push the node to the top of the stack, and have it send isBound
        // TRUE.
        //
        this->bound_nodes.push_back(&nav_info);
        nav_info.is_bound_.value(true);
        node::emit_event(nav_info.is_bound_emitter_, timestamp);

        this->browser().active_navigation_info(nav_info);
    }

    /**
     * @brief Remove a navigation_info_node from the bound node stack.
     *
     * @param nav_info    the node to unbind.
     * @param timestamp     the current time.
     */
    void
    navigation_info_class::
    unbind(navigation_info_node & nav_info, const double timestamp)
        throw ()
    {
        using std::find;

        const bound_nodes_t::iterator pos = find(this->bound_nodes.begin(),
                                                 this->bound_nodes.end(),
                                                 &nav_info);
        if (pos != this->bound_nodes.end()) {
            nav_info.is_bound_.value(false);
            node::emit_event(nav_info.is_bound_emitter_, timestamp);

            if (pos == this->bound_nodes.end() - 1
                && this->bound_nodes.size() > 1) {
                navigation_info_node & newActive =
                    dynamic_cast<navigation_info_node &>(
                        **(this->bound_nodes.end() - 2));
                newActive.is_bound_.value(true);
                node::emit_event(newActive.is_bound_emitter_, timestamp);

                this->browser().active_navigation_info(nav_info);
            } else {
                this->browser().reset_default_navigation_info();
            }
            this->bound_nodes.erase(pos);
        }
    }

    /**
     * @brief node_class-specific initialization.
     *
     * @param initial_viewpoint the viewpoint_node that should be bound
     *                          initially.
     * @param timestamp         the current time.
     */
    void
    navigation_info_class::
    do_initialize(openvrml::viewpoint_node *, const double timestamp)
        throw ()
    {
        if (this->first) {
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

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating NavigationInfo nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by navigation_info_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    navigation_info_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 7> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sfbool_id,
                           "set_bind"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "avatarSize"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "headlight"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "speed"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "type"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "visibilityLimit"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isBound")
        };

        typedef node_type_impl<navigation_info_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & navigationInfoNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        navigation_info_node::set_bind_listener>(
                            &navigation_info_node::set_bind_listener_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mffloat> >(
                            &navigation_info_node::avatar_size_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mffloat> >(
                            &navigation_info_node::avatar_size_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mffloat> >(
                            &navigation_info_node::avatar_size_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sfbool> >(
                            &navigation_info_node::headlight_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sfbool> >(
                            &navigation_info_node::headlight_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sfbool> >(
                            &navigation_info_node::headlight_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::speed_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::speed_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::speed_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mfstring> >(
                            &navigation_info_node::type_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mfstring> >(
                            &navigation_info_node::type_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<mfstring> >(
                            &navigation_info_node::type_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::visibility_limit_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::visibility_limit_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::
                        exposedfield<sffloat> >(
                            &navigation_info_node::visibility_limit_)));
            } else if (*interface == *++supported_interface) {
                navigationInfoNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<navigation_info_node>::sfbool_emitter>(
                            &navigation_info_node::is_bound_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class navigation_info_node
     *
     * @brief NavigationInfo node instances.
     */

    /**
     * @var class navigation_info_node::navigation_info_class
     *
     * @brief Class object for NavigationInfo nodes.
     */

    /**
     * @internal
     *
     * @class navigation_info_node::set_bind_listener
     *
     * @brief set_bind eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  navigation_info_node.
     */
    navigation_info_node::set_bind_listener::
    set_bind_listener(navigation_info_node & node):
        node_event_listener(node),
        event_listener_base<navigation_info_node>(node),
        sfbool_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    navigation_info_node::set_bind_listener::
    ~set_bind_listener() throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param bind      bind state.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    navigation_info_node::set_bind_listener::
    do_process_event(const sfbool & bind,
                     const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            navigation_info_node & node =
                dynamic_cast<navigation_info_node &>(this->node());
            navigation_info_class & node_class =
                const_cast<navigation_info_class &>(
                    static_cast<const navigation_info_class &>(
                        this->node().type().node_class()));
            if (bind.value()) {
                node_class.bind(node, timestamp);
            } else {
                node_class.unbind(node, timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var navigation_info_node::set_bind_listener navigation_info_node::set_bind_listener_
     *
     * @brief set_bind eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<navigation_info_node>::exposedfield<openvrml::mffloat> navigation_info_node::avatar_size_
     *
     * @brief avatarSize exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<navigation_info_node>::exposedfield<openvrml::sfbool> navigation_info_node::headlight_
     *
     * @brief headlight exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<navigation_info_node>::exposedfield<openvrml::sffloat> navigation_info_node::speed_
     *
     * @brief speed exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<navigation_info_node>::exposedfield<openvrml::mfstring> navigation_info_node::type_
     *
     * @brief type exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<navigation_info_node>::exposedfield<openvrml::sffloat> navigation_info_node::visibility_limit_
     *
     * @brief visibilityLimit exposedField.
     */

    /**
     * @var openvrml::sfbool navigation_info_node::is_bound_
     *
     * @brief isBound eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter navigation_info_node::is_bound_emitter_
     *
     * @brief isBound eventOut emitter.
     */

    const float navigation_avatar_size_[] = { 0.25f, 1.6f, 0.75f };
    const std::string navigation_type_[] = { "WALK", "ANY" };

    /**
     * @brief Construct.
     *
     * @param t     the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    navigation_info_node::
    navigation_info_node(const node_type & t,
                         const boost::shared_ptr<openvrml::scope> & scope):
        node(t, scope),
        bounded_volume_node(t, scope),
        child_node(t, scope),
        abstract_node<navigation_info_node>(t, scope),
        openvrml::navigation_info_node(t, scope),
        set_bind_listener_(*this),
        avatar_size_(*this, std::vector<float>(navigation_avatar_size_,
                                               navigation_avatar_size_ + 3)),
        headlight_(*this, true),
        speed_(*this, 1.0),
        type_(*this, std::vector<std::string>(navigation_type_,
                                              navigation_type_ + 2)),
        visibility_limit_(*this, 0.0),
        is_bound_emitter_(*this, this->is_bound_)
    {}

    /**
     * @brief Destroy.
     */
    navigation_info_node::~navigation_info_node() throw ()
    {}

    /**
     * @brief The avatar size.
     *
     * @return the avatar size.
     */
    const std::vector<float> &
    navigation_info_node::avatar_size() const throw ()
    {
        return this->avatar_size_.mffloat::value();
    }

    /**
     * @brief The headlight state.
     *
     * @return @c true if the headlight is on; @c false otherwise.
     */
    bool navigation_info_node::headlight() const throw ()
    {
        return this->headlight_.sfbool::value();
    }

    /**
     * @brief The speed.
     *
     * @return the speed.
     */
    float navigation_info_node::speed() const throw ()
    {
        return this->speed_.sffloat::value();
    }

    /**
     * @brief The navigation type.
     *
     * @return the navigation type.
     */
    const std::vector<std::string> &
    navigation_info_node::type() const throw ()
    {
        return this->type_.mfstring::value();
    }

    /**
     * @brief The visibility limit.
     *
     * @return the visibility limit.
     */
    float navigation_info_node::visibility_limit() const
        throw ()
    {
        return this->visibility_limit_.sffloat::value();
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     */
    void
    navigation_info_node::do_initialize(double) throw ()
    {
        using boost::polymorphic_downcast;

        navigation_info_class & node_class =
            const_cast<navigation_info_class &>(
                *polymorphic_downcast<const navigation_info_class *>(
                    &this->node::type().node_class()));
        if (!node_class.has_first()) { node_class.set_first(*this); }
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    navigation_info_node::
    do_shutdown(const double timestamp) throw ()
    {
        using boost::polymorphic_downcast;

        navigation_info_class & node_class =
            const_cast<navigation_info_class &>(
                *polymorphic_downcast<const navigation_info_class *>(
                    &this->node::type().node_class()));
        node_class.unbind(*this, timestamp);

        if (node_class.is_first(*this)) { node_class.reset_first(); }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    normal_class::normal_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    normal_class::~normal_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Normal nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by normal_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    normal_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface supportedInterface =
            node_interface(node_interface::exposedfield_id,
                           field_value::mfvec3f_id,
                           "vector");

        typedef node_type_impl<normal_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & normalNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                normalNodeType.add_exposedfield(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<normal_node>::exposedfield<mfvec3f> >(
                            &normal_node::vector_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<normal_node>::exposedfield<mfvec3f> >(
                            &normal_node::vector_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<normal_node>::exposedfield<mfvec3f> >(
                            &normal_node::vector_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class normal_node
     *
     * @brief Normal node instances.
     */

    /**
     * @var normal_node::normal_class
     *
     * @brief Class object for Normal nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<normal_node>::exposedfield<openvrml::mfvec3f> normal_node::vector_
     *
     * @brief vector exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    normal_node::
    normal_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<normal_node>(type, scope),
        openvrml::normal_node(type, scope),
        vector_(*this)
    {}

    /**
     * @brief Destroy.
     */
    normal_node::~normal_node() throw ()
    {}

    /**
     * @brief Get the array of normal vectors.
     *
     * @return the array of normal vectors.
     */
    const std::vector<openvrml::vec3f> &
    normal_node::vector() const throw ()
    {
        return this->vector_.mfvec3f::value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    normal_interpolator_class::
    normal_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    normal_interpolator_class::~normal_interpolator_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating NormalInterpolator nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  normal_interpolator_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    normal_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
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
                           field_value::mfvec3f_id,
                           "value_changed")
        };

        typedef node_type_impl<normal_interpolator_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & normalInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                normalInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        normal_interpolator_node::set_fraction_listener>(
                            &normal_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
                normalInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mffloat> >(
                            &normal_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mffloat> >(
                            &normal_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mffloat> >(
                            &normal_interpolator_node::key_)));
            } else if (*interface == *++supported_interface) {
                normalInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &normal_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &normal_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<normal_interpolator_node>::
                        exposedfield<mfvec3f> >(
                            &normal_interpolator_node::key_value_)));
            } else if (*interface == *++supported_interface) {
                normalInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<normal_interpolator_node>::mfvec3f_emitter>(
                            &normal_interpolator_node::value_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class normal_interpolator_node
     *
     * @brief NormalInterpolator node instances.
     */

    /**
     * @var class normal_interpolator_node::normal_interpolator_class
     *
     * @brief Class object for NormalInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class normal_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  normal_interpolator_node.
     */
    normal_interpolator_node::set_fraction_listener::
    set_fraction_listener(normal_interpolator_node & node):
        node_event_listener(node),
        event_listener_base<normal_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    normal_interpolator_node::set_fraction_listener::
    ~set_fraction_listener()
        throw ()
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
    normal_interpolator_node::set_fraction_listener::
    do_process_event(const sffloat & fraction, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            using std::vector;

            normal_interpolator_node & node =
                dynamic_cast<normal_interpolator_node &>(this->node());

            const vector<float> & key = node.key_.mffloat::value();
            const vector<vec3f> & key_value = node.key_value_.mfvec3f::value();
            vector<vec3f> value = node.value_changed_.mfvec3f::value();

            size_t nNormals = key_value.size() / key.size();
            size_t n = key.size() - 1;

            if (fraction.value() < key[0]) {
                value.assign(key_value.begin(), key_value.begin() + nNormals);
            } else if (fraction.value() > key[n]) {
                value.assign(key_value.begin() + n * nNormals,
                             key_value.begin() + (n + 1) * nNormals);
            } else {
                // Reserve enough space for the new value
                value.resize(nNormals);

                for (size_t i = 0; i < n; ++i) {
                    if (key[i] <= fraction.value()
                        && fraction.value() <= key[i + 1]) {

                        vector<vec3f>::const_iterator v1 =
                            key_value.begin() + i * nNormals;
                        vector<vec3f>::const_iterator v2 =
                            key_value.begin() + (i + 1) * nNormals;

                        const float f =
                            (fraction.value() - key[i])
                            / (key[i + 1] - key[i]);

                        // Interpolate on the surface of unit sphere.
                        for (size_t j = 0; j < nNormals; ++j) {
                            using openvrml_::fequal;

                            float alpha, beta;
                            const float dot_product = v1->dot(*v2);
                            if (!fequal<float>()(dot_product, 1.0f)
                                && v1->normalize() != v2->normalize()) {
                                // Vectors are not opposite and not coincident.
                                const float omega = float(acos(dot_product));
                                const float sinomega = float(sin(omega));
                                alpha =
                                    float(sin((1.0 - f) * omega)) / sinomega;
                                beta = float(sin(f * omega)) / sinomega;
                            } else {
                                // Do linear interpolation.
                                alpha = 1.0f - f;
                                beta = f;
                            }
                            value[j] = (alpha * *v1) + (beta * *v2);

                            ++v1;
                            ++v2;
                        }
                        break;
                    }
                }
            }

            node.value_changed_.mfvec3f::value(value);

            // Send the new value
            node::emit_event(node.value_changed_emitter_, timestamp);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var normal_interpolator_node::set_fraction_listener normal_interpolator_node::set_fraction_listener_
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<normal_interpolator_node>::exposedfield<openvrml::mffloat> normal_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<normal_interpolator_node>::exposedfield<openvrml::mfvec3f> normal_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::mfvec3f normal_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut value.
     */

    /**
     * @var openvrml::mfvec3f_emitter normal_interpolator_node::value_changed_emitter_
     *
     * @brief value_changed eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    normal_interpolator_node::
    normal_interpolator_node(const node_type & type,
                             const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<normal_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_emitter_(*this, this->value_changed_)
    {}

    /**
     * @brief Destroy.
     */
    normal_interpolator_node::~normal_interpolator_node()
        throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    orientation_interpolator_class::
    orientation_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    orientation_interpolator_class::
    ~orientation_interpolator_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating OrientationInterpolator nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  orientation_interpolator_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    orientation_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sffloat_id,
                           "set_fraction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "key"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfrotation_id,
                           "keyValue"),
            node_interface(node_interface::eventout_id,
                           field_value::sfrotation_id,
                           "value_changed")
        };

        typedef node_type_impl<orientation_interpolator_node>
            node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & orientationInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                orientationInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        orientation_interpolator_node::set_fraction_listener>(
                            &orientation_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
                orientationInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mffloat> >(
                            &orientation_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mffloat> >(
                            &orientation_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mffloat> >(
                            &orientation_interpolator_node::key_)));
            } else if (*interface == *++supported_interface) {
                orientationInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mfrotation> >(
                            &orientation_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mfrotation> >(
                            &orientation_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<orientation_interpolator_node>::
                        exposedfield<mfrotation> >(
                            &orientation_interpolator_node::key_value_)));
            } else if (*interface == *++supported_interface) {
                orientationInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<orientation_interpolator_node>::
                        sfrotation_emitter>(
                            &orientation_interpolator_node::value_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class orientation_interpolator_node
     *
     * @brief OrientationInterpolator node instances.
     */

    /**
     * @var class orientation_interpolator_node::orientation_interpolator_class
     *
     * @brief Class object for OrientationInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class orientation_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  orientation_interpolator_node.
     */
    orientation_interpolator_node::set_fraction_listener::
    set_fraction_listener(orientation_interpolator_node & node):
        node_event_listener(node),
        event_listener_base<orientation_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    orientation_interpolator_node::set_fraction_listener::
    ~set_fraction_listener() throw ()
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
    orientation_interpolator_node::set_fraction_listener::
    do_process_event(const sffloat & fraction, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            using std::vector;

            orientation_interpolator_node & node =
                dynamic_cast<orientation_interpolator_node &>(this->node());

            const vector<float> & key = node.key_.mffloat::value();
            const vector<rotation> & key_value =
                node.key_value_.mfrotation::value();

            size_t n = key.size() - 1;
            if (fraction.value() < key[0]) {
                node.value_changed_.value(key_value[0]);
            } else if (fraction.value() > key[n]) {
                node.value_changed_.value(key_value[n]);
            } else {
                for (size_t i = 0; i < n; ++i) {
                    if (key[i] <= fraction.value()
                        && fraction.value() <= key[i + 1]) {
                        using openvrml_::pi;

                        const rotation & v1 = key_value[i];
                        const rotation & v2 = key_value[i + 1];

                        // Interpolation factor
                        const float f =
                            (fraction.value() - key[i])
                            / (key[i + 1] - key[i]);

                        float x, y, z, r1, r2;
                        r1 = v1[3];

                        // Make sure the vectors are not pointing opposite ways
                        if (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] < 0.0) {
                            x = v1[0] + f * (-v2[0] - v1[0]);
                            y = v1[1] + f * (-v2[1] - v1[1]);
                            z = v1[2] + f * (-v2[2] - v1[2]);
                            r2 = -v2[3];
                        } else {
                            x = v1[0] + f * (v2[0] - v1[0]);
                            y = v1[1] + f * (v2[1] - v1[1]);
                            z = v1[2] + f * (v2[2] - v1[2]);
                            r2 = v2[3];
                        }

                        // Interpolate angles via the shortest direction
                        if (fabs(r2 - r1) > pi) {
                            if (r2 > r1) {
                                r1 += float(2.0 * pi);
                            } else {
                                r2 += float(2.0 * pi);
                            }
                        }
                        float angle = r1 + f * (r2 - r1);
                        if (angle >= 2.0 * pi) {
                            angle -= float(2.0 * pi);
                        } else if (angle < 0.0) {
                            angle += float(2.0 * pi);
                        }
                        const rotation value(vec3f(x, y, z).normalize(),
                                             angle);
                        node.value_changed_.value(value);
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
     * @var orientation_interpolator_node::set_fraction_listener orientation_interpolator_node::set_fraction_listener_
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<orientation_interpolator_node>::exposedfield<openvrml::mffloat> orientation_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<orientation_interpolator_node>::exposedfield<openvrml::mfrotation> orientation_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::sfrotation orientation_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut value.
     */

    /**
     * @var openvrml::sfrotation_emitter orientation_interpolator_node::value_changed_emitter_
     *
     * @brief value_changed eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    orientation_interpolator_node::
    orientation_interpolator_node(
        const node_type & type,
        const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<orientation_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_emitter_(*this, this->value_changed_)
    {}

    /**
     * @brief Destroy.
     */
    orientation_interpolator_node::
    ~orientation_interpolator_node() throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    pixel_texture_class::
    pixel_texture_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    pixel_texture_class::~pixel_texture_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating PixelTexture nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by pixel_texture_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    pixel_texture_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 3> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfimage_id,
                           "image"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatS"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "repeatT")
        };

        typedef node_type_impl<pixel_texture_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & pixelTextureNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end(); ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                pixelTextureNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<pixel_texture_node>::exposedfield<sfimage> >(
                            &pixel_texture_node::image_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<pixel_texture_node>::exposedfield<sfimage> >(
                            &pixel_texture_node::image_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<pixel_texture_node>::exposedfield<sfimage> >(
                            &pixel_texture_node::image_)));
            } else if (*interface == *++supported_interface) {
                pixelTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &pixel_texture_node::repeat_s_)));
            } else if (*interface == *++supported_interface) {
                pixelTextureNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &pixel_texture_node::repeat_t_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class pixel_texture_node
     *
     * @brief Represents PixelTexture node instances.
     */

    /**
     * @var pixel_texture_node::pixel_texture_class
     *
     * @brief Class object for PixelTexture nodes.
     */

    /**
     * @var openvrml::sfimage pixel_texture_node::image_
     *
     * @brief image exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope the scope to which the node belongs.
     */
    pixel_texture_node::
    pixel_texture_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_texture_node<pixel_texture_node>(type, scope),
        image_(*this)
    {}

    /**
     * @brief Destroy.
     */
    pixel_texture_node::~pixel_texture_node() throw ()
    {
        // viewer.remove_texture_object(this->texObject); ...
    }

    /**
     * @brief The image.
     *
     * @return the image.
     */
    const openvrml::image &
    pixel_texture_node::image() const throw ()
    {
        return this->image_.sfimage::value();
    }

    /**
     * @brief render_texture implementation.
     *
     * @param v viewer.
     *
     * @return object identifier for the inserted texture.
     */
    openvrml::viewer::texture_object_t
    pixel_texture_node::do_render_texture(viewer & v)
    {
        return v.insert_texture(this->image_.sfimage::value(),
                                this->repeat_s_.value(),
                                this->repeat_t_.value(),
                                true);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node class object.
     */
    plane_sensor_class::
    plane_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    plane_sensor_class::~plane_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating PlaneSensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by plane_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    plane_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "autoOffset"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec2f_id,
                           "maxPosition"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec2f_id,
                           "minPosition"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "offset"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "trackPoint_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "translation_changed")
        };

        typedef node_type_impl<plane_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & planeSensorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                planeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::auto_offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::auto_offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::auto_offset_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfbool> >(
                            &plane_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::max_position_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::max_position_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::max_position_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::min_position_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::min_position_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec2f> >(
                            &plane_sensor_node::min_position_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec3f> >(
                            &plane_sensor_node::offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec3f> >(
                            &plane_sensor_node::offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::exposedfield<sfvec3f> >(
                            &plane_sensor_node::offset_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::sfbool_emitter>(
                            &plane_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::sfvec3f_emitter>(
                            &plane_sensor_node::track_point_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                planeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<plane_sensor_node>::sfvec3f_emitter>(
                            &plane_sensor_node::translation_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class plane_sensor_node
     *
     * The PlaneSensor node maps pointing device motion into two-dimensional
     * translation in a plane parallel to the <var>z</var>&nbsp;=&nbsp;0 plane
     * of the local coordinate system. The PlaneSensor node uses the descendent
     * geometry of its parent node to determine whether it is liable to
     * generate events.
     */

    /**
     * @var plane_sensor_node::plane_sensor_class
     *
     * @brief Class object for PlaneSensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfbool> plane_sensor_node::auto_offset_
     *
     * @brief autoOffset exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfbool> plane_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec2f> plane_sensor_node::max_position_
     *
     * @brief maxPosition exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec2f> plane_sensor_node::min_position_
     *
     * @brief minPosition exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<plane_sensor_node>::exposedfield<openvrml::sfvec3f> plane_sensor_node::offset_
     *
     * @brief offset exposedField.
     */

    /**
     * @var openvrml::sfbool plane_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter plane_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::track_point_changed_
     *
     * @brief trackPoint_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter plane_sensor_node::track_point_changed_emitter_
     *
     * @brief trackPoint_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::translation_changed_
     *
     * @brief translation_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter plane_sensor_node::translation_changed_emitter_
     *
     * @brief translation_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f plane_sensor_node::activationPoint
     *
     * @brief The point at which the PlaneSensor was activated.
     */

    /**
     * @var openvrml::mat4f plane_sensor_node::activationMatrix
     *
     * @brief Activation matrix.
     */

    /**
     * @var openvrml::mat4f plane_sensor_node::modelview
     *
     * @brief The modelview matrix.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    plane_sensor_node::
    plane_sensor_node(const node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<plane_sensor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        auto_offset_(*this, true),
        enabled_(*this, true),
        max_position_(*this, vec2f(-1.0, -1.0)),
        min_position_(*this, vec2f(0.0, 0.0)),
        offset_(*this, vec3f(0.0, 0.0, 0.0)),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        track_point_changed_emitter_(*this, this->track_point_changed_),
        translation_changed_emitter_(*this, this->translation_changed_)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    plane_sensor_node::~plane_sensor_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * Render a frame if there is one available.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    plane_sensor_node::
    do_render_child(openvrml::viewer &, const rendering_context context)
    {
        //
        // Store the ModelView matrix which is calculated at the time of rendering
        // in render-context. This matrix will be in use at the time of activation.
        //
        this->modelview = context.matrix();
    }

    /**
     * @brief Activate the plane sensor.
     *
     * @todo The local coords are computed for one instance; do we need to
     *       convert @p p to local coords for each instance (USE) of the
     *       sensor?
     *
     * @param timestamp the current time.
     * @param over      whether the pointer is over affected geometry.
     * @param active    whether the pointer is active; e.g., the mouse button
     *                  is depressed.
     * @param p         the point on the affected geometry "under" the pointer.
     */
    void
    plane_sensor_node::do_activate(const double timestamp,
                                   bool,
                                   const bool active,
                                   const double (&p)[3])
    {
        if (this->enabled_.sfbool::value()) {
            if (active && !this->is_active_.value()) {
                // Become active
                this->is_active_.value(active);

                vec3f V(static_cast<float>(p[0]),
                        static_cast<float>(p[1]),
                        static_cast<float>(p[2]));
                this->activationMatrix = this->modelview.inverse();
                V *= this->activationMatrix;
                this->activationPoint.value(V);
                node::emit_event(this->is_active_emitter_, timestamp);
            } else if (!active && this->is_active_.value()) {
                // Become inactive
                this->is_active_.value(active);
                node::emit_event(this->is_active_emitter_, timestamp);

                // auto offset
                if (this->auto_offset_.sfbool::value()) {
                    this->offset_.sfvec3f::value(
                        this->translation_changed_.value());
                    node::emit_event(this->offset_, timestamp);
                }
            } else if (active) {
                // Tracking
                vec3f V(static_cast<float>(p[0]),
                        static_cast<float>(p[1]),
                        static_cast<float>(p[2]));
                V *= this->activationMatrix;
                this->track_point_changed_.value(V);
                node::emit_event(this->track_point_changed_emitter_,
                                 timestamp);

                vec3f t(V[0] - this->activationPoint.value().x()
                        + this->offset_.sfvec3f::value().x(),
                        V[1] - this->activationPoint.value().y()
                        + this->offset_.sfvec3f::value().y(),
                        0.0);

                const vec2f & min_pos = this->min_position_.sfvec2f::value();
                const vec2f & max_pos = this->max_position_.sfvec2f::value();

                if (min_pos.x() == max_pos.x()) {
                    t.x(min_pos.x());
                } else if (min_pos.x() < max_pos.x()) {
                    if (t.x() < min_pos.x()) {
                        t.x(min_pos.x());
                    } else if (t.x() > max_pos.x()) {
                        t.x(max_pos.x());
                    }
                }

                if (min_pos.y() == max_pos.y()) {
                    t.y(min_pos.y());
                } else if (min_pos.y() < max_pos.y()) {
                    if (t.y() < min_pos.y()) {
                        t.y(min_pos.y());
                    } else if (t.y() > max_pos.y()) {
                        t.y(max_pos.y());
                    }
                }

                this->translation_changed_.value(t);
                node::emit_event(this->translation_changed_emitter_,
                                 timestamp);
            }
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this class object.
     */
    point_light_class::
    point_light_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    point_light_class::~point_light_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating PointLight nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by point_light_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    point_light_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 7> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "ambientIntensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "attenuation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "intensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "location"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "on"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "radius")
        };

        typedef node_type_impl<point_light_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & pointLightNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::ambient_intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::ambient_intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::ambient_intensity_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::attenuation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::attenuation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::attenuation_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sfcolor> >(
                            &point_light_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sfcolor> >(
                            &point_light_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sfcolor> >(
                            &point_light_node::color_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::intensity_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::location_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::location_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sfvec3f> >(
                            &point_light_node::location_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sfbool> >(
                            &point_light_node::on_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sfbool> >(
                            &point_light_node::on_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sfbool> >(
                            &point_light_node::on_)));
            } else if (*interface == *++supported_interface) {
                pointLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::radius_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::radius_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_light_node>::exposedfield<sffloat> >(
                            &point_light_node::radius_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class point_light_node
     *
     * @brief PointLight node instances.
     */

    /**
     * @var point_light_node::point_light_class
     *
     * @brief Class object for PointLight instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<point_light_node>::exposedfield<openvrml::sfvec3f> point_light_node::attenuation_
     *
     * @brief attenuation exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<point_light_node>::exposedfield<openvrml::sfvec3f> point_light_node::location_
     *
     * @brief location exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<point_light_node>::exposedfield<openvrml::sffloat> point_light_node::radius_
     *
     * @brief radius exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    point_light_node::
    point_light_node(const node_type & type,
                     const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        light_node(type, scope),
        abstract_light_node<point_light_node>(type, scope),
        scoped_light_node(type, scope),
        attenuation_(*this, vec3f(1.0, 0.0, 0.0)),
        location_(*this, vec3f(0.0, 0.0, 0.0)),
        radius_(*this, 100)
    {}

    /**
     * @brief Destroy.
     */
    point_light_node::~point_light_node() throw ()
    {}

    /**
     * @brief Render the scoped light.
     *
     * This should be called before rendering any geometry nodes in the scene.
     * Since this is called from Scene::render() before traversing the
     * scene graph, the proper transformation matrix hasn't been set up.
     * Somehow it needs to figure out the accumulated xforms of its
     * parents and apply them before rendering. This is not easy with
     * DEF/USEd nodes...
     *
     * @param viewer    a viewer.
     */
    void
    point_light_node::do_render_scoped_light(viewer & v)
    {
        if (this->on_.sfbool::value() && this->radius_.sffloat::value() > 0.0)
        {
            v.insert_point_light(this->ambient_intensity_.sffloat::value(),
                                 this->attenuation_.sfvec3f::value(),
                                 this->color_.sfcolor::value(),
                                 this->intensity_.sffloat::value(),
                                 this->location_.sfvec3f::value(),
                                 this->radius_.sffloat::value());
        }
        this->node::modified(false);
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    point_light_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_scoped_light(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    point_light_node::do_shutdown(double)
        throw ()
    {
        assert(this->scene());
        this->scene()->browser().remove_scoped_light(*this);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    point_set_class::
    point_set_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    point_set_class::~point_set_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating PointSet nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by point_set_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    point_set_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 2> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "coord")
        };

        typedef node_type_impl<point_set_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & pointSetNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                pointSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::color_)));
            } else if (*interface == *++supported_interface) {
                pointSetNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::coord_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::coord_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<point_set_node>::exposedfield<sfnode> >(
                            &point_set_node::coord_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class point_set_node
     *
     * @brief Represents PointSet node instances.
     */

    /**
     * @var point_set_node::point_set_class
     *
     * @brief Class object for PointSet instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<point_set_node>::exposedfield<openvrml::sfnode> point_set_node::color_
     *
     * @brief color exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<point_set_node>::exposedfield<openvrml::sfnode> point_set_node::coord_
     *
     * @brief coord exposedField.
     */

    /**
     * @var openvrml::bounding_sphere point_set_node::bsphere
     *
     * @brief Bounding volume.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope the scope to which the node belongs.
     */
    point_set_node::
    point_set_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<point_set_node>(type, scope),
        geometry_node(type, scope),
        color_(*this),
        coord_(*this)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    point_set_node::~point_set_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool point_set_node::modified() const
    {
        return this->node::modified()
            || (this->color_.sfnode::value()
                && this->color_.sfnode::value()->modified())
            || (this->coord_.sfnode::value()
                && this->coord_.sfnode::value()->modified());
    }

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    point_set_node::
    do_render_geometry(openvrml::viewer & viewer,
                       const rendering_context context)
    {
        using std::vector;

        if (context.draw_bounding_spheres) {
            assert(dynamic_cast<const bounding_sphere *>
                   (&this->bounding_volume()));
            const bounding_sphere & bs =
                static_cast<const bounding_sphere &>(this->bounding_volume());
            viewer.draw_bounding_sphere(bs, bounding_volume::intersection(4));
        }

        openvrml::coordinate_node * const coordinateNode =
            node_cast<openvrml::coordinate_node *>(
                this->coord_.sfnode::value().get());
        const vector<vec3f> & coord = coordinateNode
            ? coordinateNode->point()
            : vector<vec3f>();

        openvrml::color_node * const colorNode =
            node_cast<openvrml::color_node *>(
                this->color_.sfnode::value().get());
        const vector<openvrml::color> & color = colorNode
            ? colorNode->color()
            : vector<openvrml::color>();

        viewer::object_t obj = viewer.insert_point_set(coord, color);

        if (colorNode) { colorNode->modified(false); }
        if (coordinateNode) { coordinateNode->modified(false); }

        return obj;
    }

    /**
     * @brief Indicate that point sets should be drawn with the emissive color.
     *
     * @return @c true.
     */
    bool point_set_node::do_emissive() const throw ()
    {
        return true;
    }

    /**
     * @brief Recalculate the bounding volume.
     */
    void point_set_node::recalc_bsphere()
    {
        this->bsphere = bounding_sphere();
        openvrml::coordinate_node * const coordinateNode =
            node_cast<openvrml::coordinate_node *>(
                this->coord_.sfnode::value().get());
        if (coordinateNode) {
            const std::vector<vec3f> & coord = coordinateNode->point();
            for(std::vector<vec3f>::const_iterator vec(coord.begin());
                vec != coord.end(); ++vec) {
                this->bsphere.extend(*vec);
            }
        }
        this->bounding_volume_dirty(false);
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    point_set_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<point_set_node *>(this)->recalc_bsphere();
        }
        return this->bsphere;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    position_interpolator_class::
    position_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    position_interpolator_class::
    ~position_interpolator_class() throw ()
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
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  position_interpolator_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    position_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
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
                           "value_changed")
        };

        typedef node_type_impl<position_interpolator_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & positionInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                positionInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        position_interpolator_node::set_fraction_listener>(
                            &position_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
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
            } else if (*interface == *++supported_interface) {
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
            } else if (*interface == *++supported_interface) {
                positionInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<position_interpolator_node>::
                        sfvec3f_emitter>(
                            &position_interpolator_node::value_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class position_interpolator_node
     *
     * @brief PositionInterpolator node instances.
     */

    /**
     * @var class position_interpolator_node::position_interpolator_class
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
        node_event_listener(node),
        event_listener_base<position_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    position_interpolator_node::set_fraction_listener::
    ~set_fraction_listener() throw ()
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
    do_process_event(const sffloat & fraction, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            using std::vector;

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
    position_interpolator_node(const node_type & type,
                               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<position_interpolator_node>(type, scope),
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
    ~position_interpolator_node() throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    proximity_sensor_class::
    proximity_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    proximity_sensor_class::~proximity_sensor_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating ProximitySensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  proximity_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    proximity_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "center"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "size"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "position_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfrotation_id,
                           "orientation_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "enterTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "exitTime")
        };

        typedef node_type_impl<proximity_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & proximitySensorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::center_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::center_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::center_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::size_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::size_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &proximity_sensor_node::size_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfbool> >(
                            &proximity_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfbool> >(
                            &proximity_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::
                        exposedfield<sfbool> >(
                            &proximity_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::sfbool_emitter>(
                            &proximity_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::sfvec3f_emitter>(
                            &proximity_sensor_node::position_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::sfrotation_emitter>(
                            &proximity_sensor_node::orientation_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::sftime_emitter>(
                            &proximity_sensor_node::enter_time_emitter_)));
            } else if (*interface == *++supported_interface) {
                proximitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<proximity_sensor_node>::sftime_emitter>(
                            &proximity_sensor_node::exit_time_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class proximity_sensor_node
     *
     * @brief Represents ProximitySensor node instances.
     */

    /**
     * @var proximity_sensor_node::proximity_sensor_class
     *
     * @brief Class object for ProximitySensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<proximity_sensor_node>::exposedfield<openvrml::sfvec3f> proximity_sensor_node::center_
     *
     * @brief center exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<proximity_sensor_node>::exposedfield<openvrml::sfbool> proximity_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<proximity_sensor_node>::exposedfield<openvrml::sfvec3f> proximity_sensor_node::size_
     *
     * @brief size exposedField.
     */

    /**
     * @var openvrml::sfbool proximity_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter proximity_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f proximity_sensor_node::position_changed_
     *
     * @brief position_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter proximity_sensor_node::position_changed_emitter_
     *
     * @brief position_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfrotation proximity_sensor_node::orientation_changed_
     *
     * @brief orientation_changed eventOut value.
     */

    /**
     * @var openvrml::sfrotation proximity_sensor_node::orientation_changed_emitter_
     *
     * @brief orientation_changed eventOut emitter.
     */

    /**
     * @var openvrml::sftime proximity_sensor_node::enter_time_
     *
     * @brief enterTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter proximity_sensor_node::enter_time_emitter_
     *
     * @brief enterTime eventOut emitter.
     */

    /**
     * @var openvrml::sftime proximity_sensor_node::exit_time_
     *
     * @brief exitTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter proximity_sensor_node::exit_time_emitter_
     *
     * @brief exitTime eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    proximity_sensor_node::
    proximity_sensor_node(const node_type & type,
                          const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<proximity_sensor_node>(type, scope),
        child_node(type, scope),
        center_(*this, vec3f(0.0, 0.0, 0.0)),
        enabled_(*this, true),
        size_(*this, vec3f(0.0, 0.0, 0.0)),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        position_changed_emitter_(*this, this->position_changed_),
        orientation_changed_emitter_(*this, this->orientation_changed_),
        enter_time_(0.0),
        enter_time_emitter_(*this, this->enter_time_),
        exit_time_(0.0),
        exit_time_emitter_(*this, this->exit_time_)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    proximity_sensor_node::~proximity_sensor_node() throw ()
    {}

    /**
     * @brief Render the node: generate proximity events.
     *
     * If necessary, events prior to the current time are generated due to
     * interpolation of enterTimes and exitTimes. The timestamp should never be
     * increased.
     *
     * This is in a render() method since the it needs the viewer position
     * with respect to the local coordinate system.
     * Could do this with Node::inverseTransform(double [4][4]) now...
     *
     * The positions and times are not interpolated to report the exact
     * place and time of entries and exits from the sensor regions as
     * required by the spec, since that would require the last viewer position
     * to be stored in the node, which is problematic in the presence of
     * DEF/USEd nodes...
     * I suppose the scene could keep the last viewer position in the global
     * coordinate system and it could be transformed all the way down the
     * scenegraph, but that sounds painful.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    proximity_sensor_node::
    do_render_child(openvrml::viewer & viewer, const rendering_context context)
    {
        if (this->enabled_.sfbool::value()
            && this->size_.sfvec3f::value().x() > 0.0
            && this->size_.sfvec3f::value().y() > 0.0
            && this->size_.sfvec3f::value().z() > 0.0
            && viewer.mode() == viewer::draw_mode) {
            using openvrml_::fabs;
            using openvrml_::fless_equal;

            sftime timeNow(browser::current_time());
            float x, y, z;

            // Is viewer inside the box?
            mat4f MV = context.matrix();
            MV = MV.inverse();
            x = MV[3][0]; y = MV[3][1]; z = MV[3][2];
            bool inside =
                fless_equal<float>()(
                    fabs(x - this->center_.sfvec3f::value().x()),
                    0.5f * this->size_.sfvec3f::value().x())
                && fless_equal<float>()(
                    fabs(y - this->center_.sfvec3f::value().y()),
                    0.5f * this->size_.sfvec3f::value().y())
                && fless_equal<float>()(
                    fabs(z - this->center_.sfvec3f::value().z()),
                    0.5f * this->size_.sfvec3f::value().z());
            bool wasIn = this->is_active_.value();

            // Check if viewer has entered the box
            if (inside && ! wasIn) {
                this->is_active_.value(true);
                node::emit_event(this->is_active_emitter_, timeNow.value());

                this->enter_time_ = timeNow;
                node::emit_event(this->enter_time_emitter_, timeNow.value());
            }

            // Check if viewer has left the box
            else if (wasIn && !inside) {
                this->is_active_.value(false);
                node::emit_event(this->is_active_emitter_, timeNow.value());

                this->exit_time_ = timeNow;
                node::emit_event(this->exit_time_emitter_, timeNow.value());
            }

            // Check for movement within the box
            if (wasIn || inside) {
                if (this->position_changed_.value() != vec3f(x, y, z)) {
                    this->position_changed_.value(vec3f(x, y, z));
                    node::emit_event(this->position_changed_emitter_,
                                     timeNow.value());
                }

                vec3f trans, scale, shear;
                rotation orientation;
                MV.transformation(trans, orientation, scale, shear);
                if (this->orientation_changed_.value() != orientation) {
                    this->orientation_changed_.value(orientation);
                    node::emit_event(this->orientation_changed_emitter_,
                                     timeNow.value());
                }
            }
        } else {
            this->node::modified(false);
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    scalar_interpolator_class::
    scalar_interpolator_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    scalar_interpolator_class::~scalar_interpolator_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating CoordinateInterpolator nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  CoordinateInterpolatorClass.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    scalar_interpolator_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sffloat_id,
                           "set_fraction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "key"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "keyValue"),
            node_interface(node_interface::eventout_id,
                           field_value::sffloat_id,
                           "value_changed")
        };

        typedef node_type_impl<scalar_interpolator_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & scalarInterpolatorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                scalarInterpolatorNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        scalar_interpolator_node::set_fraction_listener>(
                            &scalar_interpolator_node::set_fraction_listener_)));
            } else if (*interface == *++supported_interface) {
                scalarInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(&scalar_interpolator_node::key_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(&scalar_interpolator_node::key_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(&scalar_interpolator_node::key_)));
            } else if (*interface == *++supported_interface) {
                scalarInterpolatorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(
                            &scalar_interpolator_node::key_value_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(
                            &scalar_interpolator_node::key_value_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<scalar_interpolator_node>::
                        exposedfield<mffloat> >(
                            &scalar_interpolator_node::key_value_)));
            } else if (*interface == *++supported_interface) {
                scalarInterpolatorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<scalar_interpolator_node>::sffloat_emitter>(
                            &scalar_interpolator_node::value_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class scalar_interpolator_node
     *
     * @brief ScalarInterpolator node instances.
     */

    /**
     * @var class scalar_interpolator_node::scalar_interpolator_class
     *
     * @brief Class object for ScalarInterpolator nodes.
     */

    /**
     * @internal
     *
     * @class scalar_interpolator_node::set_fraction_listener
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  scalar_interpolator_node.
     */
    scalar_interpolator_node::set_fraction_listener::
    set_fraction_listener(scalar_interpolator_node & node):
        node_event_listener(node),
        event_listener_base<scalar_interpolator_node>(node),
        sffloat_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    scalar_interpolator_node::set_fraction_listener::
    ~set_fraction_listener() throw ()
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
    scalar_interpolator_node::set_fraction_listener::
    do_process_event(const sffloat & fraction, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            using std::vector;

            scalar_interpolator_node & node =
                dynamic_cast<scalar_interpolator_node &>(this->node());

            const vector<float> & key = node.key_.mffloat::value();
            const vector<float> & key_value = node.key_value_.mffloat::value();

            vector<float>::size_type n = key.size() - 1;
            if (fraction.value() < key[0]) {
                node.value_changed_.value(key_value[0]);
            } else if (fraction.value() > key[n]) {
                node.value_changed_.value(key_value[n]);
            } else {
                for (vector<float>::size_type i = 0; i < n; ++i) {
                    if (key[i] <= fraction.value()
                        && fraction.value() <= key[i + 1]) {
                        float v1 = key_value[i];
                        float v2 = key_value[i + 1];

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
     * @var scalar_interpolator_node::set_fraction_listener scalar_interpolator_node::set_fraction_listener_
     *
     * @brief set_fraction eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<scalar_interpolator_node>::exposedfield<openvrml::mffloat> scalar_interpolator_node::key_
     *
     * @brief key exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<scalar_interpolator_node>::exposedfield<openvrml::mffloat> scalar_interpolator_node::key_value_
     *
     * @brief keyValue exposedField.
     */

    /**
     * @var openvrml::sffloat scalar_interpolator_node::value_changed_
     *
     * @brief value_changed eventOut value.
     */

    /**
     * @var openvrml::sffloat_emitter scalar_interpolator_node::value_changed_emitter_
     *
     * @brief value_changed eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    scalar_interpolator_node::
    scalar_interpolator_node(const node_type & type,
                             const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<scalar_interpolator_node>(type, scope),
        child_node(type, scope),
        set_fraction_listener_(*this),
        key_(*this),
        key_value_(*this),
        value_changed_emitter_(*this, this->value_changed_)
    {}

    /**
     * @brief Destroy.
     */
    scalar_interpolator_node::~scalar_interpolator_node()
        throw ()
    {}


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    shape_class::shape_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    shape_class::~shape_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Shape nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by shape_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    shape_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 2> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "appearance"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "geometry")
        };

        typedef node_type_impl<shape_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & shapeNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                shapeNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::appearance_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::appearance_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::appearance_)));
            } else if (*interface == *++supported_interface) {
                shapeNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::geometry_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::geometry_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<shape_node>::exposedfield<sfnode> >(
                            &shape_node::geometry_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class shape_node
     *
     * @brief Represents Shape node instances.
     */

    /**
     * @var shape_node::shape_class
     *
     * @brief Class object for Shape instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<shape_node>::exposedfield<openvrml::sfnode> shape_node::appearance_
     *
     * @brief appearance exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<shape_node>::exposedfield<openvrml::sfnode> shape_node::geometry_
     *
     * @brief geometry exposedField.
     */

    /**
     * @var openvrml::viewer::object_t shape_node::viewerObject
     *
     * @brief A reference to the node's previously used rendering data.
     *
     * If supported by the Viewer implementation, this member holds a reference
     * to the node's rendering data once the node has already been rendered
     * once. The intent is to capitalize on USE references in the VRML scene
     * graph.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node.
     * @param scope     the scope to which the node belongs.
     */
    shape_node::
    shape_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<shape_node>(type, scope),
        child_node(type, scope),
        appearance_(*this),
        geometry_(*this),
        viewerObject(0)
    {}

    /**
     * @brief Destroy.
     */
    shape_node::~shape_node() throw ()
    {
        // need viewer to free viewerObject ...
    }

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool shape_node::modified() const
    {
        return this->node::modified()
            || (this->geometry_.sfnode::value()
                && this->geometry_.sfnode::value()->modified())
            || (this->appearance_.sfnode::value()
                && this->appearance_.sfnode::value()->modified());
    }

    /**
     * @brief Render the node.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    shape_node::
    do_render_child(openvrml::viewer & viewer, const rendering_context context)
    {
        openvrml::appearance_node * const appearance =
            node_cast<openvrml::appearance_node *>(
                this->appearance_.sfnode::value().get());
        openvrml::material_node * const material =
            appearance
            ? node_cast<openvrml::material_node *>(
                appearance->material().get())
            : 0;
        geometry_node * const geometry =
            node_cast<geometry_node *>(this->geometry_.sfnode::value().get());

        //
        // If the appearance has changed, we need to rerender the geometry.
        //
        if (geometry && appearance && appearance->modified()) {
            geometry->modified(true);
        }

        if (this->viewerObject && (this->modified()
                                   || (appearance && appearance->modified())
                                   || (geometry && geometry->modified()))) {
            viewer.remove_object(this->viewerObject);
            this->viewerObject = 0;
        }

        if (this->viewerObject) {
            viewer.insert_reference(this->viewerObject);
        } else if (geometry) {
            this->viewerObject = viewer.begin_object(this->id().c_str());

            // Don't care what color it is if we are picking
            bool picking = (viewer::pick_mode == viewer.mode());
            if (!picking) {
                size_t texture_components = 0;

                if (appearance) {
                    appearance->render_appearance(viewer, context);

                    texture_node * const texture =
                        node_cast<texture_node *>(appearance->texture().get());
                    if (texture) {
                        texture_components = texture->image().comp();
                    }
                } else {
                    viewer.enable_lighting(false);  // turn lighting off
                    set_unlit_material(viewer);
                }

                // hack for opengl material mode
                viewer.set_material_mode(texture_components,
                                         geometry->color());

                //
                // Set the drawing color.
                //
                // Most geometries are drawn using the diffuse color; but some
                // (notably point and line sets) are drawn with the emissive
                // color.
                //
                color c(1.0, 1.0, 1.0);
                float transparency = 0.0;
                if (material) {
                    if (geometry && geometry->emissive()) {
                        c = material->emissive_color();
                    } else {
                        c = material->diffuse_color();
                    }
                    transparency = material->transparency();
                }
                viewer.set_color(c, transparency);
            }

            geometry->render_geometry(viewer, context);

            viewer.end_object();
        }
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    shape_node::do_bounding_volume() const
    {
        //
        // just pass off to the geometry's getbvolume() method
        //
        bounded_volume_node * bv =
            node_cast<bounded_volume_node *>(
                this->geometry_.sfnode::value().get());
        const openvrml::bounding_volume & result = bv
            ? bv->bounding_volume()
            : this->bounded_volume_node::do_bounding_volume();
        const_cast<shape_node *>(this)->bounding_volume_dirty(false);
        return result;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    sound_class::sound_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    sound_class::~sound_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Sound nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by sound_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    sound_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 10> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "direction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "intensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "location"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "maxBack"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "maxFront"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "minBack"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "minFront"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "priority"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "source"),
            node_interface(node_interface::field_id,
                           field_value::sfbool_id,
                           "spatialize")
        };

        typedef node_type_impl<sound_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & soundNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::direction_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::direction_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::direction_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::intensity_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::location_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::location_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sfvec3f> >(
                            &sound_node::location_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_back_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_back_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_back_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_front_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_front_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::max_front_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_back_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_back_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_back_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_front_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_front_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::min_front_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::priority_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::priority_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sffloat> >(
                            &sound_node::priority_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sound_node>::exposedfield<sfnode> >(
                            &sound_node::source_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sound_node>::exposedfield<sfnode> >(
                            &sound_node::source_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sound_node>::exposedfield<sfnode> >(
                            &sound_node::source_)));
            } else if (*interface == *++supported_interface) {
                soundNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfbool>(
                            &sound_node::spatialize_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class sound_node
     *
     * @brief Represents Sound node instances.
     */

    /**
     * @var sound_node::sound_class
     *
     * @brief Class object for Sound instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sfvec3f> sound_node::direction_
     *
     * @brief direction exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::intensity_
     *
     * @brief intensity exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sfvec3f> sound_node::location_
     *
     * @brief location exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::max_back_
     *
     * @brief maxBack exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::max_front_
     *
     * @brief maxFront exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::min_back_
     *
     * @brief minBack exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::min_front_
     *
     * @brief minFront exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sffloat> sound_node::priority_
     *
     * @brief priority exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sound_node>::exposedfield<openvrml::sfnode> sound_node::source_
     *
     * @brief source exposedField.
     */

    /**
     * @var openvrml::sfbool sound_node::spatialize_
     *
     * @brief spatialize field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope associated with the instance.
     */
    sound_node::
    sound_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<sound_node>(type, scope),
        child_node(type, scope),
        direction_(*this, vec3f(0, 0, 1)),
        intensity_(*this, 1.0f),
        location_(*this),
        max_back_(*this, 10.0f),
        max_front_(*this, 10.0f),
        min_back_(*this, 1.0f),
        min_front_(*this, 1.0f),
        priority_(*this),
        source_(*this),
        spatialize_(true)
    {}

    /**
     * @brief Destroy.
     */
    sound_node::~sound_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * @param viewer    a Viewer.
     * @param context   a rendering context.
     */
    void
    sound_node::
    do_render_child(openvrml::viewer & /* viewer */,
                    const rendering_context /* context */)
    {
        // If this clip has been modified, update the internal data
        if (this->source_.sfnode::value()
            && this->source_.sfnode::value()->modified()) {
//        this->source.value->render(viewer, context);
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    sphere_class::sphere_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    sphere_class::~sphere_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Sphere nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by sphere_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    sphere_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface
            supportedInterface(node_interface::field_id,
                               field_value::sffloat_id,
                               "radius");

        typedef node_type_impl<sphere_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & spereNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                spereNodeType.add_field(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sffloat>(
                            &sphere_node::radius)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class sphere_node
     *
     * @brief Sphere node instances.
     */

    /**
     * @var sphere_node::sphere_class
     *
     * @brief Class object for Sphere instances.
     */

    /**
     * @var openvrml::sffloat sphere_node::radius
     *
     * @brief radius field.
     */

    /**
     * @var openvrml::bounding_sphere sphere_node::bsphere
     *
     * @brief Bounding volume.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    sphere_node::
    sphere_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<sphere_node>(type, scope),
        geometry_node(type, scope),
        radius(1.0)
    {
        this->bounding_volume_dirty(true); // lazy calc of bvolumes
    }

    /**
     * @brief Destroy.
     */
    sphere_node::~sphere_node() throw ()
    {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    sphere_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        const viewer::object_t object_ref =
            viewer.insert_sphere(this->radius.value());
        return object_ref;
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    sphere_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<sphere_node *>(this)
                ->bsphere.radius(this->radius.value());
            const_cast<sphere_node *>(this)
                ->bounding_volume_dirty(false); // logical const
        }
        return this->bsphere;
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    sphere_sensor_class::
    sphere_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    sphere_sensor_class::~sphere_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating SphereSensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by sphere_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    sphere_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 6> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "autoOffset"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfrotation_id,
                           "offset"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sfrotation_id,
                           "rotation_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "trackPoint_changed")
        };

        typedef node_type_impl<sphere_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & sphereSensorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::auto_offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::auto_offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::auto_offset_)));
            } else if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::exposedfield<sfbool> >(
                            &sphere_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<sphere_sensor_node>::
                        exposedfield<sfrotation> >(&sphere_sensor_node::offset_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<sphere_sensor_node>::
                        exposedfield<sfrotation> >(&sphere_sensor_node::offset_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::
                        exposedfield<sfrotation> >(&sphere_sensor_node::offset_)));
            } else if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::sfbool_emitter>(
                            &sphere_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::sfrotation_emitter>(
                            &sphere_sensor_node::rotation_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                sphereSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<sphere_sensor_node>::sfvec3f_emitter>(
                            &sphere_sensor_node::track_point_changed_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class sphere_sensor_node
     *
     * @brief SphereSensor node instances.
     */

    /**
     * @var sphere_sensor_node::sphere_sensor_class
     *
     * @brief Class object for SphereSensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sphere_sensor_node>::exposedfield<openvrml::sfbool> sphere_sensor_node::auto_offset_
     *
     * @brief autoOffset exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sphere_sensor_node>::exposedfield<openvrml::sfbool> sphere_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<sphere_sensor_node>::exposedfield<openvrml::sfrotation> sphere_sensor_node::offset_
     *
     * @brief offset exposedField.
     */

    /**
     * @var openvrml::sfbool sphere_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter sphere_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sfrotation sphere_sensor_node::rotation_changed_
     *
     * @brief rotation_changed eventOut value.
     */

    /**
     * @var openvrml::sfrotation_emitter sphere_sensor_node::rotation_changed_emitter_
     *
     * @brief rotation_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f sphere_sensor_node::track_point_changed_
     *
     * @brief trackPoint_changed eventOut.
     */

    /**
     * @var openvrml::sfvec3f_emitter sphere_sensor_node::track_point_changed_emitter_
     *
     * @brief trackPoint_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f sphere_sensor_node::activationPoint
     *
     * @brief The start point of a drag operation.
     */

    /**
     * @var openvrml::sfvec3f sphere_sensor_node::centerPoint
     *
     * @brief Center point.
     */

    /**
     * @var openvrml::mat4f sphere_sensor_node::modelview
     *
     * @brief Modelview matrix.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    sphere_sensor_node::
    sphere_sensor_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<sphere_sensor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        auto_offset_(*this, true),
        enabled_(*this, true),
        offset_(*this, openvrml::rotation(0.0, 1.0, 0.0, 0.0)),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        rotation_changed_emitter_(*this, this->rotation_changed_),
        track_point_changed_emitter_(*this, this->track_point_changed_)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    sphere_sensor_node::~sphere_sensor_node() throw ()
    {}

    /**
     * @brief Render the node.
     *
     * @param viewer    a viewer.
     * @param context   a rendering context.
     */
    void
    sphere_sensor_node::
    do_render_child(openvrml::viewer &, const rendering_context context)
    {
        //
        // Store the ModelView matrix which is calculated at the time of
        // rendering in render-context. This matrix will be in use at the time
        // of activation
        //
        this->modelview = context.matrix();
    }

    /**
     * @brief Activate or deactivate the sphere_sensor_node.
     *
     * Activating a drag sensor means that the pointing device button has been
     * depressed and a drag operation has been initiated. The sensor is
     * deactivated when the button is released at the end of the operation.
     *
     * @param timestamp the current time.
     * @param over      @c true if the pointer is over affected geometry;
     *                  @c false otherwise.
     * @param active    @c true if the drag operation is in progress; @c false
     *                  otherwise.
     * @param p         the pointing device position.
     */
    void
    sphere_sensor_node::do_activate(double timestamp,
                                    bool,
                                    bool active,
                                    const double (&p)[3])
    {
        if (this->enabled_.sfbool::value()) {
            // Become active
            if (active && !this->is_active_.value()) {
                this->is_active_.value(active);

                // set activation point in world coords
                const vec3f floatVec(static_cast<float>(p[0]),
                                     static_cast<float>(p[1]),
                                     static_cast<float>(p[2]));
                this->activationPoint.value(floatVec);

                if (this->auto_offset_.sfbool::value()) {
                    this->rotation_changed_ = this->offset_;
                }

                // calculate the center of the object in world coords
                vec3f V;
                mat4f M = this->modelview.inverse();
                V = V * M;
                this->centerPoint.value(V);

                // send message
                node::emit_event(this->is_active_emitter_, timestamp);
            }
            // Become inactive
            else if (!active && this->is_active_.value()) {
                this->is_active_.value(active);
                node::emit_event(this->is_active_emitter_, timestamp);

                // save auto offset of rotation
                if (this->auto_offset_.sfbool::value()) {
                    this->offset_.sfrotation::value(
                        this->rotation_changed_.value());
                    node::emit_event(this->offset_, timestamp);
                }
            }
            // Tracking
            else if (active) {
                // get local coord for touch point
                vec3f V(static_cast<float>(p[0]),
                        static_cast<float>(p[1]),
                        static_cast<float>(p[2]));
                mat4f M = this->modelview.inverse();
                V = V * M;
                this->track_point_changed_.value(V);
                node::emit_event(this->track_point_changed_emitter_,
                                 timestamp);

                vec3f V2(static_cast<float>(p[0]),
                         static_cast<float>(p[1]),
                         static_cast<float>(p[2]));
                vec3f tempv = V2 - this->centerPoint.value();
                vec3f dir1(tempv);

                //
                // Get the length of the pre-normalized vector.
                //
                const float dist = dir1.length();

                dir1 = dir1.normalize();
                tempv =
                    this->activationPoint.value() - this->centerPoint.value();
                vec3f dir2(tempv);
                dir2 = dir2.normalize();

                tempv = dir1 * dir2;
                vec3f cx(tempv);
                cx = cx.normalize();

                openvrml::rotation newRot(cx,
                                          dist * float(acos(dir1.dot(dir2))));
                if (this->auto_offset_.sfbool::value()) {
                    newRot = newRot * this->offset_.sfrotation::value();
                }
                this->rotation_changed_.value(newRot);

                node::emit_event(this->rotation_changed_emitter_, timestamp);
            }
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    spot_light_class::
    spot_light_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    spot_light_class::~spot_light_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating SpotLight nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by spot_light_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    spot_light_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 10> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "ambientIntensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "attenuation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "beamWidth"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfcolor_id,
                           "color"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "cutOffAngle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "direction"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "intensity"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "location"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "on"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "radius")
        };

        typedef node_type_impl<spot_light_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & spotLightNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::ambient_intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::ambient_intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::ambient_intensity_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::attenuation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::attenuation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::attenuation_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::beam_width_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::beam_width_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::beam_width_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfcolor> >(
                            &spot_light_node::color_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfcolor> >(
                            &spot_light_node::color_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfcolor> >(
                            &spot_light_node::color_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::cut_off_angle_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::cut_off_angle_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::cut_off_angle_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::direction_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::direction_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::direction_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::intensity_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::intensity_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::intensity_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::location_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::location_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfvec3f> >(
                            &spot_light_node::location_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfbool> >(
                            &spot_light_node::on_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfbool> >(
                            &spot_light_node::on_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sfbool> >(
                            &spot_light_node::on_)));
            } else if (*interface == *++supported_interface) {
                spotLightNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::radius_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::radius_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<spot_light_node>::exposedfield<sffloat> >(
                            &spot_light_node::radius_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class spot_light_node
     *
     * @brief SpotLight node instances.
     */

    /**
     * @var spot_light_node::spot_light_class
     *
     * @brief Class object for SpotLight instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<openvrml::sfvec3f> spot_light_node::attenuation_
     *
     * @brief attenuation exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<sffloat> spot_light_node::beam_width_
     *
     * @brief beamWidth exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<openvrml::sffloat> spot_light_node::cut_off_angle_
     *
     * @brief cutOffAngle exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<openvrml::sfvec3f> spot_light_node::direction_
     *
     * @brief direction exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<openvrml::sfvec3f> spot_light_node::location_
     *
     * @brief location exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<spot_light_node>::exposedfield<openvrml::sffloat> spot_light_node::radius_
     *
     * @brief radius exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope the scope to which the node belongs.
     */
    spot_light_node::
    spot_light_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        light_node(type, scope),
        abstract_light_node<spot_light_node>(type, scope),
        scoped_light_node(type, scope),
        attenuation_(*this, vec3f(1.0, 0.0, 0.0)),
        beam_width_(*this, 1.570796f),
        cut_off_angle_(*this, 0.785398f),
        direction_(*this, vec3f(0.0, 0.0, -1.0)),
        location_(*this, vec3f(0.0, 0.0, 0.0)),
        radius_(*this, 100)
    {}

    /**
     * @brief Destroy.
     */
    spot_light_node::~spot_light_node() throw ()
    {}

    /**
     * @brief Render the scoped light.
     *
     * @param viewer    a Viewer.
     *
     * @todo This should be called before rendering any geometry in the scene.
     *      Since this is called from Scene::render before traversing the
     *      scene graph, the proper transformation matrix hasn't been set up.
     *      Somehow it needs to figure out the accumulated xforms of its
     *      parents and apply them before rendering. This is not easy with
     *      DEF/USEd nodes...
     */
    void
    spot_light_node::do_render_scoped_light(viewer & v)
    {
        if (this->on_.sfbool::value() && this->radius_.sffloat::value() > 0.0)
        {
            v.insert_spot_light(this->ambient_intensity_.sffloat::value(),
                                this->attenuation_.sfvec3f::value(),
                                this->beam_width_.sffloat::value(),
                                this->color_.sfcolor::value(),
                                this->cut_off_angle_.sffloat::value(),
                                this->direction_.sfvec3f::value(),
                                this->intensity_.sffloat::value(),
                                this->location_.sfvec3f::value(),
                                this->radius_.sffloat::value());
        }
        this->node::modified(false);
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    spot_light_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_scoped_light(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    spot_light_node::do_shutdown(double)
        throw ()
    {
        assert(this->scene());
        this->scene()->browser().remove_scoped_light(*this);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    switch_class::switch_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    switch_class::~switch_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Switch nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by switch_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    switch_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 2> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "choice"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfint32_id,
                           "whichChoice")
        };

        typedef node_type_impl<switch_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & switchNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                switchNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        switch_node::choice_exposedfield>(&switch_node::choice_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        switch_node::choice_exposedfield>(&switch_node::choice_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        switch_node::choice_exposedfield>(&switch_node::choice_)));
            } else if (*interface == *++supported_interface) {
                switchNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        switch_node::which_choice_exposedfield>(
                            &switch_node::which_choice_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        switch_node::which_choice_exposedfield>(
                            &switch_node::which_choice_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        switch_node::which_choice_exposedfield>(
                            &switch_node::which_choice_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class switch_node
     *
     * @brief Switch node instances.
     */

    /**
     * @var class switch_node::switch_class
     *
     * @brief Class object for Switch nodes.
     */

    /**
     * @internal
     *
     * @class switch_node::choice_exposedfield
     *
     * @brief choice exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  switch_node.
     */
    switch_node::choice_exposedfield::
    choice_exposedfield(switch_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfnode_listener(node),
        exposedfield<openvrml::mfnode>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    switch_node::choice_exposedfield::
    choice_exposedfield(const choice_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfnode_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfnode>(obj)
    {}

    /**
     * @brief Destroy.
     */
    switch_node::choice_exposedfield::~choice_exposedfield()
        throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    switch_node::choice_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new choice_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param choice    choice nodes.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    switch_node::choice_exposedfield::
    event_side_effect(const mfnode &, double) throw (std::bad_alloc)
    {
        try {
            switch_node & n =
                dynamic_cast<switch_node &>(this->node_event_listener::node());

            const int32 which_choice = n.which_choice_.sfint32::value();
            assert(!n.children_.value().empty());
            typedef std::vector<boost::intrusive_ptr<openvrml::node> >
                children_t;
            children_t children = n.children_.value();
            children[0] =
                (which_choice >= 0
                 && which_choice < int32(n.choice_.mfnode::value().size()))
                ? n.choice_.mfnode::value()[which_choice]
                : children_t::value_type(0);
            n.children_.value(children);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class switch_node::which_choice_exposedfield
     *
     * @brief choice exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  switch_node.
     */
    switch_node::which_choice_exposedfield::
    which_choice_exposedfield(switch_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfint32_listener(node),
        exposedfield<openvrml::sfint32>(node, -1)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    switch_node::which_choice_exposedfield::
    which_choice_exposedfield(const which_choice_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfint32_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfint32>(obj)
    {}

    /**
     * @brief Destroy.
     */
    switch_node::which_choice_exposedfield::
    ~which_choice_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    switch_node::which_choice_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new which_choice_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param which_choice  choice nodes.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    switch_node::which_choice_exposedfield::
    event_side_effect(const sfint32 & which_choice, double)
        throw (std::bad_alloc)
    {
        try {
            switch_node & n =
                dynamic_cast<switch_node &>(this->node_event_listener::node());

            assert(!n.children_.value().empty());
            typedef std::vector<boost::intrusive_ptr<openvrml::node> >
                children_t;
            children_t children = n.children_.value();
            children[0] =
                ((which_choice.value() >= 0)
                 && (which_choice.value()
                     < int32(n.choice_.mfnode::value().size())))
                ? n.choice_.mfnode::value()[which_choice.value()]
                : children_t::value_type(0);
            n.children_.value(children);
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var switch_node::choice_exposedfield switch_node::choice_
     *
     * @brief choice exposedField.
     */

    /**
     * @var switch_node::which_choice_exposedfield switch_node::which_choice_
     *
     * @brief whichChoice exposedField.
     */

    /**
     * @var openvrml::mfnode switch_node::children_
     *
     * @brief The children currently in the scene graph.
     */

    /**
     * @var openvrml::bounding_sphere switch_node::bsphere
     *
     * @brief Cached copy of the bsphere enclosing this node's children.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    switch_node::
    switch_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<switch_node>(type, scope),
        grouping_node(type, scope),
        choice_(*this),
        which_choice_(*this),
        children_(1)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    switch_node::~switch_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool switch_node::modified() const
    {
        if (this->node::modified()) { return true; }

        long w = this->which_choice_.sfint32::value();

        return w >= 0 && size_t(w) < this->choice_.mfnode::value().size()
            && this->choice_.mfnode::value()[w]->modified();
    }

    /**
     * @brief Render the node.
     *
     * The child corresponding to @a whichChoice is rendered. Nothing is
     * rendered if @a whichChoice is -1.
     *
     * @param viewer    a Viewer.
     * @param context   a rendering context.
     */
    void
    switch_node::
    do_render_child(openvrml::viewer & viewer, const rendering_context context)
    {
        assert(!this->children_.value().empty());
        child_node * const child =
            node_cast<child_node *>(this->children_.value()[0].get());
        if (child) { child->render_child(viewer, context); }
        this->node::modified(false);
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    switch_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<switch_node *>(this)->recalc_bsphere();
        }
        return this->bsphere;
    }

    /**
     * @brief Get the children in the scene graph.
     *
     * @return the child nodes in the scene graph.
     */
    const std::vector<boost::intrusive_ptr<openvrml::node> > &
    switch_node::do_children() const throw ()
    {
        return this->children_.value();
    }

    /**
     * @brief Recalculate the bounding volume.
     */
    void switch_node::recalc_bsphere()
    {
        this->bsphere = bounding_sphere();
        long w = this->which_choice_.sfint32::value();
        if (w >= 0 && size_t(w) < this->choice_.mfnode::value().size()) {
            const boost::intrusive_ptr<node> & node = this->choice_.mfnode::value()[w];
            bounded_volume_node * bounded_volume =
                node_cast<bounded_volume_node *>(node.get());
            if (bounded_volume) {
                const openvrml::bounding_volume & ci_bv =
                    bounded_volume->bounding_volume();
                this->bsphere.extend(ci_bv);
            }
        }
        this->bounding_volume_dirty(false);
    }


    /**
     * @var FT_Library text_class::freeTypeLibrary
     *
     * @brief FreeType library handle.
     *
     * @see http://freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Library
     */

    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    text_class::text_class(openvrml::browser & browser):
        node_class(browser)
    {
# if OPENVRML_ENABLE_RENDER_TEXT_NODE
        FT_Error error = 0;
        error = FT_Init_FreeType(&this->freeTypeLibrary);
        if (error) {
            browser.err << "error initializing FreeType library" << std::endl;
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

    /**
     * @brief Destroy.
     */
    text_class::~text_class() throw ()
    {
# if OPENVRML_ENABLE_RENDER_TEXT_NODE
        FT_Error error = 0;
        error = FT_Done_FreeType(this->freeTypeLibrary);
        if (error) {
            this->browser().err << "error shutting down FreeType library"
                                << std::endl;
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Text nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by text_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    text_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::mfstring_id,
                           "string"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfnode_id,
                           "fontStyle"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mffloat_id,
                           "length"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "maxExtent")
        };

        typedef node_type_impl<text_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & textNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                textNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        text_node::string_exposedfield>(&text_node::string_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<text_node::string_exposedfield>(
                            &text_node::string_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        text_node::string_exposedfield>(&text_node::string_)));
            } else if (*interface == *++supported_interface) {
                textNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        text_node::font_style_exposedfield>(
                            &text_node::font_style_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        text_node::font_style_exposedfield>(
                            &text_node::font_style_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        text_node::font_style_exposedfield>(
                            &text_node::font_style_)));
            } else if (*interface == *++supported_interface) {
                textNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        text_node::length_exposedfield>(&text_node::length_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<text_node::length_exposedfield>(
                            &text_node::length_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        text_node::length_exposedfield>(&text_node::length_)));
            } else if (*interface == *++supported_interface) {
                textNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        text_node::max_extent_exposedfield>(
                            &text_node::max_extent_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        text_node::max_extent_exposedfield>(
                            &text_node::max_extent_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        text_node::max_extent_exposedfield>(
                            &text_node::max_extent_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class text_node
     *
     * @brief Text node instances.
     */

    /**
     * @var class text_node::text_class
     *
     * @brief Class object for Text nodes.
     */

    /**
     * @internal
     *
     * @class text_node::string_exposedfield
     *
     * @brief string exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  text_node.
     */
    text_node::string_exposedfield::
    string_exposedfield(text_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(node),
        exposedfield<openvrml::mfstring>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    text_node::string_exposedfield::
    string_exposedfield(const string_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mfstring_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mfstring>(obj)
    {}

    /**
     * @brief Destroy.
     */
    text_node::string_exposedfield::
    ~string_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    text_node::string_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new string_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param string    text strings.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    text_node::string_exposedfield::
    event_side_effect(const mfstring &, double)
        throw (std::bad_alloc)
    {
        try {
            text_node & node =
                dynamic_cast<text_node &>(this->node_event_listener::node());
            node.update_ucs4();
            node.update_geometry();
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class text_node::font_style_exposedfield
     *
     * @brief fontStyle exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  text_node.
     */
    text_node::font_style_exposedfield::
    font_style_exposedfield(text_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfnode_listener(node),
        exposedfield<openvrml::sfnode>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    text_node::font_style_exposedfield::
    font_style_exposedfield(const font_style_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfnode_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfnode>(obj)
    {}

    /**
     * @brief Destroy.
     */
    text_node::font_style_exposedfield::~font_style_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    text_node::font_style_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new font_style_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param font_style    text strings.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    text_node::font_style_exposedfield::
    event_side_effect(const sfnode &, double)
        throw (std::bad_alloc)
    {
        try {
            text_node & node =
                dynamic_cast<text_node &>(this->node_event_listener::node());
            node.update_ucs4();
            node.update_geometry();
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class text_node::length_exposedfield
     *
     * @brief length exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  text_node.
     */
    text_node::length_exposedfield::
    length_exposedfield(text_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mffloat_listener(node),
        exposedfield<openvrml::mffloat>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    text_node::length_exposedfield::
    length_exposedfield(const length_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        mffloat_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::mffloat>(obj)
    {}

    /**
     * @brief Destroy.
     */
    text_node::length_exposedfield::~length_exposedfield()
        throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    text_node::length_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new length_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param length    length of the text strings.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    text_node::length_exposedfield::
    event_side_effect(const mffloat &, double)
        throw (std::bad_alloc)
    {
        try {
            text_node & node =
                dynamic_cast<text_node &>(this->node_event_listener::node());
            node.update_geometry();
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class text_node::max_extent_exposedfield
     *
     * @brief maxExtent exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  text_node.
     */
    text_node::max_extent_exposedfield::
    max_extent_exposedfield(text_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sffloat_listener(node),
        exposedfield<openvrml::sffloat>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    text_node::max_extent_exposedfield::
    max_extent_exposedfield(const max_extent_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sffloat_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sffloat>(obj)
    {}

    /**
     * @brief Destroy.
     */
    text_node::max_extent_exposedfield::
    ~max_extent_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    text_node::max_extent_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new max_extent_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param max_extent    maximum extent of the text strings.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    text_node::max_extent_exposedfield::
    event_side_effect(const sffloat &, double)
        throw (std::bad_alloc)
    {
        try {
            text_node & node =
                dynamic_cast<text_node &>(this->node_event_listener::node());
            node.update_geometry();
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var text_node::string_exposedfield text_node::string_
     *
     * @brief string exposedField.
     */

    /**
     * @var text_node::font_style_exposedfield text_node::font_style_
     *
     * @brief fontStyle exposedField.
     */

    /**
     * @var text_node::length_exposedfield text_node::length_
     *
     * @brief length exposedField.
     */

    /**
     * @var text_node::max_extent_exposedfield text_node::max_extent_
     *
     * @brief maxExtent exposedField.
     */

    /**
     * @internal
     *
     * @struct text_node::glyph_geometry
     *
     * @brief Used to hold the geometry of individual glyphs.
     */

    /**
     * @var std::vector<openvrml::vec2f> text_node::glyph_geometry::coord
     *
     * @brief Glyph coordinates.
     */

    /**
     * @var std::vector<openvrml::int32> text_node::glyph_geometry::coord_index
     *
     * @brief Glyph coordinate indices.
     */

    /**
     * @var float text_node::glyph_geometry::advance_width
     *
     * @brief The distance the pen should advance horizontally after drawing
     *        the glyph.
     */

    /**
     * @var float text_node::glyph_geometry::advance_height
     *
     * @brief The distance the pen should advance vertically after drawing the
     *      glyph.
     */

# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE

    /**
     * @internal
     *
     * @brief Determine whether three vertices are ordered counter-clockwise.
     *
     * Does not throw.
     *
     * @param p0 first vertex.
     * @param p1 second vertex.
     * @param p2 third vertex.
     *
     * @return 1 if the vertices are counter-clockwise, -1 if the vertices are
     *         clockwise, or 0 if the vertices are neither.
     */
    OPENVRML_LOCAL int ccw_(const openvrml::vec2f & p0,
                            const openvrml::vec2f & p1,
                            const openvrml::vec2f & p2)
        throw ()
    {
        const float dx1 = p1.x() - p0.x();
        const float dy1 = p1.y() - p0.y();
        const float dx2 = p2.x() - p0.x();
        const float dy2 = p2.y() - p0.y();

        if (dx1 * dy2 > dy1 * dx2) { return 1; }
        if (dx1 * dy2 < dy1 * dx2) { return -1; }
        if ((dx1 * dx2 < 0) || (dy1 * dy2 < 0)) return -1;
        if ((dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2)) { return 1; }
        return 0;
    }

    /**
     * @internal
     *
     * @brief Determine whether two line segments intersect.
     *
     * Does not throw.
     *
     * @param l0p0 first point of the first line.
     * @param l0p1 second point of the first line.
     * @param l1p0 first point of the second line.
     * @param l1p1 second point of the second line.
     *
     * @return @c true if the line segments intersect; @c false otherwise.
     */
    OPENVRML_LOCAL bool intersect_(const openvrml::vec2f & l0p0,
                                   const openvrml::vec2f & l0p1,
                                   const openvrml::vec2f & l1p0,
                                   const openvrml::vec2f & l1p1)
        throw ()
    {
        return ccw_(l0p0, l0p1, l1p0) * ccw_(l0p0, l0p1, l1p1) <= 0
            && ccw_(l1p0, l1p1, l0p0) * ccw_(l1p0, l1p1, l0p1) <= 0;
    }

    /**
     * @brief Determine whether a line segment intersects any line segments
     *        in a contour.
     *
     * Does not throw.
     *
     * @param v0      initial vertex of the line segment.
     * @param v1      final vertex of the line segment.
     * @param contour a contour (a series of line segments).
     *
     * @return @c true if the line segment defined by (@p v0, @p v1)
     *         intersects any line segment in @p contour; @c false otherwise.
     */
    OPENVRML_LOCAL bool
    intersects_segment_in_contour(const openvrml::vec2f & v0,
                                  const openvrml::vec2f & v1,
                                  const std::vector<openvrml::vec2f> & contour)
        throw ()
    {
        for (size_t j = 0; j < contour.size() - 1; ++j) {
            using openvrml::vec2f;
            //
            // Endpoints of the segment to test for intersection.
            //
            const vec2f & contour_v0 = contour[j];
            const vec2f & contour_v1 = contour[j + 1];
            //
            // We don't care if the endpoints match (and the intersection
            // test will treat this as an intersection).
            //
            if (contour_v0 == v0 || contour_v0 == v1
                || contour_v1 == v0 || contour_v1 == v1) { continue; }
            if (intersect_(v0, v1, contour_v0, contour_v1)) { return true; }
        }
        return false;
    }

    /**
     * @internal
     *
     * @brief Get the exterior vertext that should be used to connect to the
     *      interior contour.
     *
     * Finds the first vertex in @p exteriorContour such that a line segment
     * from the interior contour vertex at @p interiorIndex through the
     * exterior contour vertex does not cross @p interiorContour.
     *
     * Does not throw.
     *
     * @param exterior_contour the exterior contour.
     * @param interior_contour the interior contour.
     * @param interior_index   the index of a vertex in @p interiorContour to
     *                         be used as the interior connecting vertex.
     *
     * @return the index of a vertex in @p exteriorContour that is usable as
     *         the exterior connecting vertex, or -1 if no such vertex is
     *         found.
     */
    OPENVRML_LOCAL long get_exterior_connecting_vertex_index_(
        const std::vector<openvrml::vec2f> & exterior_contour,
        const std::vector<const std::vector<openvrml::vec2f> *> &
        interior_contours,
        const openvrml::vec2f & interior_vertex)
        throw ()
    {
        assert(exterior_contour.size() > 1);
        assert(!interior_contours.empty());

        using openvrml::vec2f;

        typedef std::vector<const std::vector<vec2f> *> interior_contours_type;

        for (size_t i = 0; i < exterior_contour.size(); ++i) {
            const vec2f & exterior_vertex = exterior_contour[i];
            bool intersects_interior = false;
            for (interior_contours_type::const_iterator interior_contour =
                     interior_contours.begin();
                 interior_contour != interior_contours.end()
                     && !intersects_interior;
                 ++interior_contour) {
                assert(*interior_contour);
                if (intersects_segment_in_contour(interior_vertex,
                                                  exterior_vertex,
                                                  **interior_contour)) {
                    intersects_interior = true;
                }
            }
            if (!intersects_interior
                && !intersects_segment_in_contour(interior_vertex,
                                                  exterior_vertex,
                                                  exterior_contour)) {
                return i;
            }
        }
        return -1;
    }

    OPENVRML_LOCAL bool
    inside_contour_(const std::vector<openvrml::vec2f> & contour,
                    const openvrml::vec2f & point)
        throw ()
    {
        using openvrml::vec2f;

        bool result = false;
        const size_t nvert = contour.size();
        for (size_t i = 0, j = nvert - 1; i < nvert; j = i++) {
            const vec2f & vi = contour[i];
            const vec2f & vj = contour[j];
            if ((((vi.y() <= point.y()) && (point.y() < vj.y()))
                 || ((vj.y() <= point.y()) && (point.y() < vi.y())))
                && (point.x() < (vj.x() - vi.x())
                    * (point.y() - vi.y()) / (vj.y() - vi.y()) + vi.x())) {
                result = !result;
            }
        }
        return result;
    }

    enum contour_type_ { exterior_, interior_ };

    OPENVRML_LOCAL contour_type_
    get_type_(const std::vector<openvrml::vec2f> & contour,
              const std::vector<std::vector<openvrml::vec2f> > & contours)
        throw ()
    {
        using std::vector;

        assert(!contour.empty());
        const openvrml::vec2f & vertex = contour[0];

        bool is_interior = false;
        for (vector<vector<openvrml::vec2f> >::const_iterator test_contour =
                 contours.begin();
             test_contour != contours.end();
             ++test_contour) {
            if (&*test_contour == &contour) { continue; }
            if (inside_contour_(*test_contour, vertex)) {
                is_interior = !is_interior;
            }
        }
        return is_interior
            ? interior_
            : exterior_;
    }

    struct OPENVRML_LOCAL polygon_ {
        const std::vector<openvrml::vec2f> * exterior;
        std::vector<const std::vector<openvrml::vec2f> *> interiors;
    };

    struct OPENVRML_LOCAL inside_ :
        std::binary_function<const std::vector<openvrml::vec2f> *,
                             const std::vector<openvrml::vec2f> *,
                             bool> {
        bool operator()(const std::vector<openvrml::vec2f> * const lhs,
                        const std::vector<openvrml::vec2f> * const rhs) const
            {
                assert(lhs);
                assert(rhs);
                assert(!lhs->empty());
                //
                // Assume contours don't intersect. So if one point on lhs is
                // inside rhs, then assume all of lhs is inside rhs.
                //
                return inside_contour_(*rhs, lhs->front());
            }
    };

    OPENVRML_LOCAL const std::vector<polygon_>
    get_polygons_(const std::vector<std::vector<openvrml::vec2f> > & contours)
        throw (std::bad_alloc)
    {
        using std::vector;
        using openvrml::vec2f;
        typedef std::multiset<const vector<vec2f> *, inside_>
            segregated_contours;

        //
        // First, divide the contours into interior and exterior contours.
        //
        segregated_contours interiors, exteriors;
        for (vector<vector<vec2f> >::const_iterator contour = contours.begin();
             contour != contours.end();
             ++contour) {
            switch (get_type_(*contour, contours)) {
            case interior_:
                interiors.insert(&*contour);
                break;
            case exterior_:
                exteriors.insert(&*contour);
                break;
            default:
                assert(false);
            }
        }

        //
        // For each exterior, find its associated interiors and group them in
        // a Polygon_.
        //
        vector<polygon_> polygons;
        while (!exteriors.empty()) {
            polygon_ polygon;
            polygon.exterior = *exteriors.begin();
            segregated_contours::iterator interior = interiors.begin();
            while (interior != interiors.end()) {
                assert(!(*interior)->empty());
                if (inside_contour_(*polygon.exterior, (*interior)->front())) {
                    polygon.interiors.push_back(*interior);
                    segregated_contours::iterator next = interior;
                    ++next;
                    interiors.erase(interior);
                    interior = next;
                } else {
                    ++interior;
                }
            }
            polygons.push_back(polygon);
            exteriors.erase(exteriors.begin());
        }
        return polygons;
    }

    OPENVRML_LOCAL long
    get_vertex_index_(const std::vector<openvrml::vec2f> & vertices,
                      const openvrml::vec2f & vertex)
        throw ()
    {
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == vertex) { return i; }
        }
        return -1;
    }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE

/**
 * @brief Construct from a set of contours.
 *
 * @param contours          a vector of closed contours that make up the
 *                          glyph's outline.
 * @param advance_width     the distance the pen should advance horizontally
 *                          after drawing the glyph.
 * @param advance_height    the distance the pen should advance vertically
 *                          after drawing the glyph.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
    text_node::glyph_geometry::
    glyph_geometry(const std::vector<std::vector<vec2f> > & contours,
                   const float advance_width,
                   const float advance_height)
        throw (std::bad_alloc):
        advance_width(advance_width),
        advance_height(advance_height)
    {
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        using std::vector;
        using openvrml::vec2f;

        const vector<polygon_> polygons = get_polygons_(contours);
        for (vector<polygon_>::const_iterator polygon = polygons.begin();
             polygon != polygons.end();
             ++polygon) {
            //
            // connectionMap is keyed on a pointer to a vertex on the exterior
            // contour, and maps to a pointer to the interior contour whose
            // first vertex is closest to the exterior vertex.
            //
            typedef std::multimap<const vec2f *, const std::vector<vec2f> *>
                connection_map_t;
            connection_map_t connection_map;

            //
            // Fill connection_map. For each interior contour, find the exterior
            // vertex that is closest to the first vertex in the interior contour,
            // and the put the pair in the map.
            //
            for (vector<const vector<vec2f> *>::const_iterator interior =
                     polygon->interiors.begin();
                 interior != polygon->interiors.end();
                 ++interior) {
                assert(*interior);
                assert(!(*interior)->empty());
                long exterior_vertex_index =
                    get_exterior_connecting_vertex_index_(*polygon->exterior,
                                                          polygon->interiors,
                                                          (*interior)->front());
                assert(exterior_vertex_index > -1);
                const vec2f * const exterior_vertex =
                    &(*polygon->exterior)[exterior_vertex_index];
                assert(exterior_vertex);
                const connection_map_t::value_type value(exterior_vertex,
                                                         *interior);
                connection_map.insert(value);
            }

            //
            // Finally, draw the polygon.
            //
            assert(!polygon->exterior->empty());
            for (size_t i = 0; i < polygon->exterior->size(); ++i) {
                const vec2f & exterior_vertex = (*polygon->exterior)[i];
                long exterior_index = get_vertex_index_(this->coord,
                                                        exterior_vertex);
                if (exterior_index > -1) {
                    this->coord_index.push_back(exterior_index);
                } else {
                    this->coord.push_back(exterior_vertex);
                    assert(!this->coord.empty());
                    exterior_index = this->coord.size() - 1;
                    this->coord_index.push_back(exterior_index);
                }
                connection_map_t::iterator pos;
                while ((pos = connection_map.find(&exterior_vertex))
                       != connection_map.end()) {
                    for (int i = pos->second->size() - 1; i > -1; --i) {
                        const vec2f & interior_vertex = (*pos->second)[i];
                        const long interior_index =
                            get_vertex_index_(this->coord, interior_vertex);
                        if (interior_index > -1) {
                            this->coord_index.push_back(interior_index);
                        } else {
                            this->coord.push_back(interior_vertex);
                            assert(!this->coord.empty());
                            this->coord_index.push_back(this->coord.size() - 1);
                        }
                    }
                    this->coord_index.push_back(exterior_index);
                    connection_map.erase(pos);
                }
            }
            assert(connection_map.empty());
            this->coord_index.push_back(-1);
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

    /**
     * @internal
     *
     * @struct text_node::text_geometry
     *
     * @brief Holds the text geometry.
     */

    /**
     * @var std::vector<openvrml::vec3f> text_node::text_geometry::coord
     *
     * @brief Text geometry coordinates.
     */

    /**
     * @var std::vector<openvrml::int32> text_node::text_geometry::coord_index
     *
     * @brief Text geometry coordinate indices.
     */

    /**
     * @var std::vector<openvrml::vec3f> text_node::text_geometry::normal
     *
     * @brief Text geometry normals.
     */

    /**
     * @var std::vector<openvrml::vec2f> text_node::text_geometry::tex_coord
     *
     * @brief Text geometry texture coordinates.
     */

    /**
     * @typedef text_node::ucs4_string_t
     *
     * @brief A vector of FcChar32 vectors.
     */

    /**
     * @typedef text_node::glyph_geometry_map_t
     *
     * @brief Maps FT_UInts to glyph_geometry.
     *
     * @see http://freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_UInt
     */

    /**
     * @var text_node::ucs4_string_t text_node::ucs4_string
     *
     * @brief UCS-4 equivalent of the (UTF-8) data in @a string.
     */

    /**
     * @var FT_Face text_node::face
     *
     * @brief Handle to the font face.
     *
     * @see http://freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Face
     */

    /**
     * @var text_node::glyph_geometry_map_t text_node::glyph_geometry_map
     *
     * @brief Map of glyph indices to glyph_geometry.
     *
     * glyph_geometry instances are created as needed as new glyphs are
     * encountered. Once they are created, they are cached in the
     * glyph_geometry_map for rapid retrieval the next time the glyph is
     * encountered.
     */

    /**
     * @var text_node::text_geometry text_node::text_geometry_
     *
     * @brief The text geometry.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    text_node::
    text_node(const node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<text_node>(type, scope),
        geometry_node(type, scope),
        string_(*this),
        font_style_(*this),
        length_(*this),
        max_extent_(*this)
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        ,face(0)
# endif
    {}

    /**
     * @brief Destroy.
     */
    text_node::~text_node() throw ()
    {}

    /**
     * @brief Determine whether the node has been modified.
     *
     * @return @c true if the node or one of its children has been modified,
     *      @c false otherwise.
     */
    bool text_node::modified() const
    {
        return this->node::modified()
            || (this->font_style_.sfnode::value()
                && this->font_style_.sfnode::value()->modified());
    }

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     */
    openvrml::viewer::object_t
    text_node::
    do_render_geometry(openvrml::viewer & viewer, rendering_context)
    {
        const viewer::object_t retval =
            viewer.insert_shell(viewer::mask_ccw,
                                this->text_geometry_.coord,
                                this->text_geometry_.coord_index,
                                std::vector<openvrml::color>(), // color
                                std::vector<int32>(), // colorIndex
                                this->text_geometry_.normal,
                                std::vector<int32>(), // normalIndex
                                this->text_geometry_.tex_coord,
                                std::vector<int32>()); // texCoordIndex
        if (this->font_style_.sfnode::value()) {
            this->font_style_.sfnode::value()->modified(false);
        }

        return retval;
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void text_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        this->update_ucs4();
        this->update_face();
        this->update_geometry();
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void text_node::do_shutdown(double)
        throw ()
    {
# if OPENVRML_ENABLE_RENDER_TEXT_NODE
        if (this->face) {
            FT_Error ftError = FT_Done_Face(this->face);
            assert(ftError == FT_Err_Ok); // Surely this can't fail.
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

    /**
     * @brief Called when @a string changes to update the UCS-4 text.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void text_node::update_ucs4() throw (std::bad_alloc)
    {
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        this->ucs4_string.clear();
        this->ucs4_string.resize(this->string_.mfstring::value().size());

        for (size_t i = 0; i < this->string_.mfstring::value().size(); ++i) {
            using std::string;
            using std::vector;

            const string & element = this->string_.mfstring::value()[i];

            vector<FcChar32> & ucs4Element = this->ucs4_string[i];

            //
            // First, we need to convert the characters from UTF-8 to UCS-4.
            //
            vector<FcChar8> utf8String(element.begin(), element.end());
            int nchar = 0, wchar = 0;
            FcBool well_formed =
                FcUtf8Len(&utf8String[0], utf8String.size(), &nchar, &wchar);
            if (well_formed) {
                ucs4Element.resize(nchar);
                vector<FcChar8>::iterator utf8interface = utf8String.begin();
                vector<FcChar32>::iterator ucs4interface = ucs4Element.begin();
                while (utf8interface != utf8String.end()) {
                    const int utf8bytes =
                        FcUtf8ToUcs4(&*utf8interface, &*ucs4interface,
                                     utf8String.end() - utf8interface);
                    utf8interface += utf8bytes;
                    ucs4interface++;
                }
            }
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE

    //
    // FcChar8_traits is a model of the standard library Character Traits
    // concept.
    //
    struct OPENVRML_LOCAL FcChar8_traits {
        typedef unsigned char char_type;
        typedef int int_type;
        typedef std::streampos pos_type;
        typedef std::streamoff off_type;
        typedef mbstate_t state_type;

        static void assign(char_type & c1, const char_type & c2);
        static bool eq(const char_type & c1, const char_type & c2);
        static bool lt(const char_type & c1, const char_type & c2);
        static int compare(const char_type * s1, const char_type * s2,
                           size_t n);
        static size_t length(const char_type * s);
        static const char_type * find(const char_type * s, size_t n,
                                      const char_type & a);
        static char_type * move(char_type * s1, const char_type * s2,
                                size_t n);
        static char_type * copy(char_type * s1, const char_type * s2,
                                size_t n);
        static char_type * assign(char_type * s, size_t n, char_type a);
        static int_type eof();
        static int_type not_eof(const int_type & c);
        static char_type to_char_type(const int_type & e);
        static int_type to_int_type(const char_type & c);
        static bool eq_int_type(const int_type & e1, const int_type & e2);
    };

    inline void FcChar8_traits::assign(char_type & c1, const char_type & c2)
    {
        c1 = c2;
    }

    inline bool FcChar8_traits::eq(const char_type & c1, const char_type & c2)
    {
        return c1 == c2;
    }

    inline bool FcChar8_traits::lt(const char_type & c1, const char_type & c2)
    {
        return c1 < c2;
    }

    inline int FcChar8_traits::compare(const char_type * s1,
                                       const char_type * s2,
                                       size_t n)
    {
        for (size_t i = 0; i < n; ++i) {
            if (!eq(s1[i], s2[i])) { return lt(s1[i], s2[i]) ? -1 : 1; }
        }
        return 0;
    }

    inline size_t FcChar8_traits::length(const char_type * s)
    {
        const char_type * p = s;
        while (*p) { ++p; }
        return (p - s);
    }

    inline FcChar8_traits::char_type *
    FcChar8_traits::move(char_type * s1, const char_type * s2, size_t n)
    {
        return reinterpret_cast<char_type *>(
            memmove(s1, s2, n * sizeof(char_type)));
    }

    inline const FcChar8_traits::char_type *
    FcChar8_traits::find(const char_type * s, size_t n, const char_type & a)
    {
        for (const char_type * p = s; size_t(p - s) < n; ++p) {
            if (*p == a) { return p; }
        }
        return 0;
    }

    inline FcChar8_traits::char_type *
    FcChar8_traits::copy(char_type * s1, const char_type * s2, size_t n)
    {
        return reinterpret_cast<char_type *>(
            memcpy(s1, s2, n * sizeof(char_type)));
    }

    inline FcChar8_traits::char_type *
    FcChar8_traits::assign(char_type * s, size_t n, char_type a)
    {
        for (char_type * p = s; p < s + n; ++p) { assign(*p, a); }
        return s;
    }

    inline FcChar8_traits::int_type FcChar8_traits::eof()
    {
        return static_cast<int_type>(-1);
    }

    inline FcChar8_traits::int_type FcChar8_traits::not_eof(const int_type & c)
    {
        return eq_int_type(c, eof()) ? int_type(0) : c;
    }

    inline FcChar8_traits::char_type
    FcChar8_traits::to_char_type(const int_type & e)
    {
        return char_type(e);
    }

    inline FcChar8_traits::int_type
    FcChar8_traits::to_int_type(const char_type & c)
    {
        return int_type(c);
    }

    inline bool FcChar8_traits::eq_int_type(const int_type & e1,
                                            const int_type & e2)
    {
        return e1 == e2;
    }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE

    /**
     * @brief Called when @a fontStyle changes to update the font face.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void text_node::update_face() throw (std::bad_alloc)
    {
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        static const char * const fcResultMessage[] = { "match",
                                                        "no match",
                                                        "type mismatch",
                                                        "no id" };

        class FontconfigError : public std::runtime_error {
        public:
            explicit FontconfigError(const FcResult result):
                std::runtime_error(fcResultMessage[result])
                {}

            virtual ~FontconfigError() throw ()
                {}
        };

        class FreeTypeError : public std::runtime_error {
        public:
            //
            // The normal build of FreeType doesn't include a means of mapping
            // error codes to human-readable strings.  There's a means of
            // letting client apps do this by defining some macros, but that's
            // too much trouble for now.
            //
            explicit FreeTypeError(FT_Error):
                std::runtime_error("FreeType error")
                {}

            virtual ~FreeTypeError() throw ()
                {}
        };

        using std::string;
        typedef std::basic_string<FcChar8, FcChar8_traits> FcChar8_string;

        FcChar8_string language;

        std::vector<string> family;
        family.push_back("SERIF");

        string style;

        openvrml::font_style_node * const fontStyle =
            node_cast<openvrml::font_style_node *>(
                this->font_style_.sfnode::value().get());
        if (fontStyle) {
            if (!fontStyle->family().empty()) {
                family = fontStyle->family();
                style = fontStyle->style();
                language.assign(fontStyle->language().begin(),
                                fontStyle->language().end());
            }
        }

        try {
            FcPattern * initialPattern = 0;
            FcPattern * matchedPattern = 0;

            try {
                using std::vector;

                string fontName;
                //
                // Set the family.
                //
                for (size_t i = 0; i < family.size(); ++i) {
                    const std::string & element = family[i];
                    if (element == "SERIF") {
                        fontName += "serif";
                    } else if (element == "SANS") {
                        fontName += "sans";
                    } else if (element == "TYPEWRITER") {
                        fontName += "monospace";
                    } else {
                        fontName += element;
                    }
                    if (i + 1 < family.size()) { fontName += ", "; }
                }

                //
                // Set the weight.
                //
                if (style.find("BOLD") != string::npos) {
                    fontName += ":bold";
                }

                //
                // Set the slant.
                //
                if (style.find("ITALIC") != string::npos) {
                    fontName += ":italic";
                }

                //
                // For now, at least, we only want outline fonts.
                //
                fontName += ":outline=True";

                initialPattern =
                    FcNameParse(FcChar8_string(fontName.begin(),
                                               fontName.end()).c_str());
                if (!initialPattern) { throw std::bad_alloc(); }

                //
                // Set the language.
                //
                if (!language.empty()) {
                    FcPatternAddString(initialPattern,
                                       FC_LANG,
                                       language.c_str());
                }

                FcConfigSubstitute(0, initialPattern, FcMatchPattern);
                FcDefaultSubstitute(initialPattern);

                FcResult result = FcResultMatch;
                matchedPattern = FcFontMatch(0, initialPattern, &result);
                if (result != FcResultMatch) { throw FontconfigError(result); }
                assert(matchedPattern);

                FcChar8 * filename = 0;
                result = FcPatternGetString(matchedPattern,
                                            FC_FILE,
                                            0,
                                            &filename);
                if (result != FcResultMatch) { throw FontconfigError(result); }

                int id = 0;
                result = FcPatternGetInteger(matchedPattern, FC_INDEX, 0, &id);
                if (result != FcResultMatch) { throw FontconfigError(result); }

                text_class & nodeClass =
                    const_cast<text_class &>(
                        static_cast<const text_class &>(
                            this->type().node_class()));

                size_t filenameLen = 0;
                for (; filename[filenameLen]; ++filenameLen) {}

                const vector<char> ftFilename(filename,
                                              filename + filenameLen + 1);

                FT_Face newFace = 0;
                FT_Error ftError = FT_Err_Ok;
                ftError = FT_New_Face(nodeClass.freeTypeLibrary,
                                      &ftFilename[0], id, &newFace);
                if (ftError) { throw FreeTypeError(ftError); }

                if (this->face) {
                    ftError = FT_Done_Face(this->face);
                    assert(ftError == FT_Err_Ok); // Surely this can't fail.
                }

                this->face = newFace;
                this->glyph_geometry_map.clear();

                FcPatternDestroy(initialPattern);
                FcPatternDestroy(matchedPattern);
            } catch (std::runtime_error & ex) {
                FcPatternDestroy(initialPattern);
                FcPatternDestroy(matchedPattern);
                throw;
            }
        } catch (std::bad_alloc & ex) {
            throw;
        } catch (FontconfigError & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        } catch (FreeTypeError & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }

# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
    struct OPENVRML_LOCAL GlyphContours_ {
        const float scale;
        std::vector<std::vector<openvrml::vec2f> > contours;

        explicit GlyphContours_(float scale);
    };

    GlyphContours_::GlyphContours_(const float scale):
        scale(scale)
    {}

    const float stepSize_ = 0.2;

    OPENVRML_LOCAL int moveTo_(FT_Vector * const to, void * const user)
        throw ()
    {
        using std::vector;
        using openvrml::vec2f;
        assert(user);
        GlyphContours_ & c = *static_cast<GlyphContours_ *>(user);
        try {
            c.contours.push_back(vector<vec2f>(1));
        } catch (std::bad_alloc & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
            return FT_Err_Out_Of_Memory;
        }
        const vec2f vertex(to->x * c.scale, to->y * c.scale);
        c.contours.back().front() = vertex;
        return 0;
    }

    OPENVRML_LOCAL int lineTo_(FT_Vector * const to, void * const user)
        throw ()
    {
        assert(user);
        GlyphContours_ & c = *static_cast<GlyphContours_ *>(user);
        const openvrml::vec2f vertex(to->x * c.scale, to->y * c.scale);
        try {
            c.contours.back().push_back(vertex);
        } catch (std::bad_alloc & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
            return FT_Err_Out_Of_Memory;
        }
        return 0;
    }

    /**
     * @brief de Casteljau's algorithm.
     *
     * This is a nice recursive algorithm defined by de-Casteljau which
     * calculates for a given control polygon the point that lies on the bezier
     * curve for any value of t, and can be used to evaluate and draw the
     * Bezier spline without using the Bernstein polynomials.
     *
     * The algorithm advances by creating in each step a polygons of degree one
     * less than the one created in the previous step until there is only one
     * point left, which is the point on the curve. The polygon vertices for
     * each step are defined by linear interpolation of two consecutive
     * vertices of the polygon from the previous step with a value of t (the
     * parameter):
     *
     * @param buffer    an array including the control points for the curve in
     *                  the first @p npoints elements. The total size of the
     *                  array must be @p npoints * @p npoints. The remaining
     *                  elements of the array will be used by the algorithm to
     *                  store temporary values.
     * @param npoints   the number of control points.
     * @param contour   the points on the curve are added to this array.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    OPENVRML_LOCAL void evaluateCurve_(openvrml::vec2f * const buffer,
                                       const size_t npoints,
                                       std::vector<openvrml::vec2f> & contour)
        throw (std::bad_alloc)
    {
        for (size_t i = 1; i <= (1 / stepSize_); i++){
            const float t = i * stepSize_; // Parametric points 0 <= t <= 1
            for (size_t j = 1; j < npoints; j++) {
                for (size_t k = 0; k < (npoints - j); k++) {
                    openvrml::vec2f & element = buffer[j * npoints + k];
                    element.x((1 - t) * buffer[(j - 1) * npoints + k][0]
                              + t * buffer[(j - 1) * npoints + k + 1][0]);
                    element.y((1 - t) * buffer[(j - 1) * npoints + k][1]
                              + t * buffer[(j - 1) * npoints + k + 1][1]);
                }
            }
            //
            // Specify next vertex to be included on curve
            //
            contour.push_back(buffer[(npoints - 1) * npoints]); // throws std::bad_alloc
        }
    }

    OPENVRML_LOCAL int conicTo_(FT_Vector * const control,
                                FT_Vector * const to,
                                void * const user)
        throw ()
    {
        using std::vector;
        using openvrml::vec2f;

        assert(control);
        assert(to);
        assert(user);

        GlyphContours_ & c = *static_cast<GlyphContours_ *>(user);

        assert(!c.contours.empty());
        vector<vec2f> & contour = c.contours.back();
        const vec2f & lastVertex = contour[contour.size() - 1];

        assert(!contour.empty());
        const size_t npoints = 3;
        vec2f buffer[npoints * npoints] = {
            vec2f(lastVertex[0], lastVertex[1]),
            vec2f(control->x * c.scale, control->y * c.scale),
            vec2f(to->x * c.scale, to->y * c.scale)
        };

        try {
            evaluateCurve_(buffer, npoints, contour);
        } catch (std::bad_alloc & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
            return FT_Err_Out_Of_Memory;
        }
        return 0;
    }

    OPENVRML_LOCAL int cubicTo_(FT_Vector * const control1,
                                FT_Vector * const control2,
                                FT_Vector * const to,
                                void * const user)
        throw ()
    {
        using std::vector;
        using openvrml::vec2f;

        assert(control1);
        assert(control2);
        assert(to);
        assert(user);

        GlyphContours_ & c = *static_cast<GlyphContours_ *>(user);

        assert(!c.contours.empty());
        vector<vec2f> & contour = c.contours.back();
        assert(!contour.empty());
        const vec2f & lastVertex = contour.back();

        static const size_t npoints = 4;
        vec2f buffer[npoints * npoints] = {
            vec2f(lastVertex[0], lastVertex[1]),
            vec2f(control1->x * c.scale, control1->y * c.scale),
            vec2f(control2->x * c.scale, control2->y * c.scale),
            vec2f(to->x * c.scale, to->y * c.scale)
        };

        try {
            evaluateCurve_(buffer, npoints, contour);
        } catch (std::bad_alloc & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
            return FT_Err_Out_Of_Memory;
        }
        return 0;
    }
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE

    /**
     * @brief Called to update @a text_geometry.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void text_node::update_geometry() throw (std::bad_alloc)
    {
# ifdef OPENVRML_ENABLE_RENDER_TEXT_NODE
        using std::pair;
        using std::string;
        using std::vector;

        bool horizontal = true;
        string justify[2] = { "BEGIN", "FIRST" };
        bool leftToRight = true;
        bool topToBottom = true;
        float size = 1.0;
        float spacing = 1.0;
        openvrml::font_style_node * fontStyle =
            node_cast<openvrml::font_style_node *>(
                this->font_style_.sfnode::value().get());
        if (fontStyle) {
            horizontal = fontStyle->horizontal();
            if (!fontStyle->justify().empty()) {
                justify[0] = fontStyle->justify()[0];
            }
            if (fontStyle->justify().size() > 1) {
                justify[1] = fontStyle->justify()[1];
            }
            leftToRight = fontStyle->left_to_right();
            topToBottom = fontStyle->top_to_bottom();
            size = fontStyle->size();
            spacing = fontStyle->spacing();
        }

        text_geometry newGeometry;
        float geometryXMin = 0.0, geometryXMax = 0.0;
        float geometryYMin = 0.0, geometryYMax = 0.0;
        size_t npolygons = 0;
        const ucs4_string_t::const_iterator stringBegin =
            this->ucs4_string.begin();
        for (ucs4_string_t::const_iterator string = stringBegin;
             string != this->ucs4_string.end();
             ++string) {
            float penPos[2] = { 0.0, 0.0 };
            const size_t line = std::distance(stringBegin, string);
            const float lineAdvance = size * spacing * line;
            if (horizontal) {
                if (topToBottom) {
                    penPos[1] -= lineAdvance;
                } else {
                    penPos[1] += lineAdvance;
                }
            } else {
                if (leftToRight) {
                    penPos[0] += lineAdvance;
                } else {
                    penPos[0] -= lineAdvance;
                }
            }

            struct LineGeometry {
                vector<vec2f> coord;
                vector<int32> coordIndex;
                float xMin, xMax;
                float yMin, yMax;

                LineGeometry(): xMin(0.0), xMax(0.0), yMin(0.0), yMax(0.0)
                    {}
            };

            LineGeometry lineGeometry;
            for (vector<FcChar32>::const_iterator character = string->begin();
                 character != string->end(); ++character) {
                assert(this->face);
                const FT_UInt glyphIndex =
                    FcFreeTypeCharIndex(this->face, *character);

                const glyph_geometry * glyphGeometry = 0;
                const glyph_geometry_map_t::iterator pos =
                    this->glyph_geometry_map.find(glyphIndex);
                if (pos != this->glyph_geometry_map.end()) {
                    glyphGeometry = &pos->second;
                } else {
                    FT_Error error = FT_Err_Ok;
                    error = FT_Load_Glyph(this->face,
                                          glyphIndex,
                                          FT_LOAD_NO_SCALE);
                    assert(error == FT_Err_Ok);
                    FT_Glyph glyph;
                    error = FT_Get_Glyph(this->face->glyph, &glyph);
                    assert(error == FT_Err_Ok);
                    static FT_Outline_Funcs outlineFuncs = { moveTo_,
                                                             lineTo_,
                                                             conicTo_,
                                                             cubicTo_,
                                                             0,
                                                             0 };
                    const float glyphScale = (this->face->bbox.yMax > 0.0)
                        ? size / this->face->bbox.yMax
                        : size;
                    GlyphContours_ glyphContours(glyphScale);
                    assert(glyph->format == ft_glyph_format_outline);
                    const FT_OutlineGlyph outlineGlyph =
                        reinterpret_cast<FT_OutlineGlyph>(glyph);
                    error = FT_Outline_Decompose(&outlineGlyph->outline,
                                                 &outlineFuncs,
                                                 &glyphContours);
                    assert(error == FT_Err_Ok);

                    assert(this->face->glyph);
                    const float advanceWidth =
                        FT_HAS_HORIZONTAL(this->face)
                        ? this->face->glyph->metrics.horiAdvance * glyphScale
                        : 0.0;
                    const float advanceHeight =
                        FT_HAS_VERTICAL(this->face)
                        ? this->face->glyph->metrics.vertAdvance * glyphScale
                        : 0.0;

                    const glyph_geometry_map_t::value_type
                        value(glyphIndex,
                              glyph_geometry(glyphContours.contours,
                                             advanceWidth,
                                             advanceHeight));
                    const pair<glyph_geometry_map_t::iterator, bool> result =
                        this->glyph_geometry_map.insert(value);
                    assert(result.second);
                    glyphGeometry = &result.first->second;
                }

                for (size_t i = 0; i < glyphGeometry->coord.size(); ++i) {
                    const vec2f & glyphVertex = glyphGeometry->coord[i];
                    const vec2f textVertex(glyphVertex[0] + penPos[0],
                                           glyphVertex[1] + penPos[1]);
                    lineGeometry.coord.push_back(textVertex);
                    lineGeometry.xMin = (lineGeometry.xMin < textVertex[0])
                        ? lineGeometry.xMin
                        : textVertex[0];
                    lineGeometry.xMax = (lineGeometry.xMax > textVertex[0])
                        ? lineGeometry.xMax
                        : textVertex[0];
                    lineGeometry.yMin = (lineGeometry.yMin < textVertex[1])
                        ? lineGeometry.yMin
                        : textVertex[1];
                    lineGeometry.yMax = (lineGeometry.yMax > textVertex[1])
                        ? lineGeometry.yMax
                        : textVertex[1];
                }

                for (size_t i = 0; i < glyphGeometry->coord_index.size(); ++i)
                {
                    const long index = glyphGeometry->coord_index[i];
                    if (index > -1) {
                        const size_t offset = lineGeometry.coord.size()
                            - glyphGeometry->coord.size();
                        lineGeometry.coordIndex.push_back(offset + index);
                    } else {
                        lineGeometry.coordIndex.push_back(-1);
                        ++npolygons;
                    }
                }
                if (horizontal) {
                    const float xAdvance = glyphGeometry->advance_width;
                    if (leftToRight) {
                        penPos[0] += xAdvance;
                    } else {
                        penPos[0] -= xAdvance;
                    }
                } else {
                    const float yAdvance = glyphGeometry->advance_height;
                    if (topToBottom) {
                        penPos[1] -= yAdvance;
                    } else {
                        penPos[1] += yAdvance;
                    }
                }
            }

            //
            // Scale to length.
            //
            const float length =
                (line < this->length_.mffloat::value().size())
                ? this->length_.mffloat::value()[line]
                : 0.0;
            if (length > 0.0) {
                const float currentLength =
                    lineGeometry.xMax - lineGeometry.xMin;
                for (size_t i = 0; i < lineGeometry.coord.size(); ++i) {
                    const vec2f & vertex = lineGeometry.coord[i];
                    const vec2f scaledVertex(vertex[0] / currentLength * length,
                                             vertex[1]);
                    lineGeometry.coord[i] = scaledVertex;
                }
            }

            //
            // Add the line to the text geometry.  We need to adjust for the
            // major alignment.
            //
            float xOffset = 0.0f, yOffset = 0.0f;
            //
            // Offset is 0 for "BEGIN" or "FIRST" (or anything else, in our
            // case).
            //
            if (justify[0] == "MIDDLE") {
                if (horizontal) {
                    xOffset =
                        -((lineGeometry.xMax - lineGeometry.xMin) / 2.0f);
                } else {
                    yOffset = (lineGeometry.yMax - lineGeometry.yMin) / 2.0f;
                }
            } else if (justify[0] == "END") {
                if (horizontal) {
                    xOffset = -(lineGeometry.xMax - lineGeometry.xMin);
                } else {
                    yOffset = lineGeometry.yMax - lineGeometry.yMin;
                }
            }
            for (size_t i = 0; i < lineGeometry.coordIndex.size(); ++i) {
                const long index = lineGeometry.coordIndex[i];
                if (index > -1) {
                    const vec2f & lineVertex = lineGeometry.coord[index];
                    const vec3f textVertex(lineVertex.x() + xOffset,
                                           lineVertex.y() + yOffset,
                                           0.0f);
                    newGeometry.coord.push_back(textVertex);
                    newGeometry.coord_index
                        .push_back(newGeometry.coord.size() - 1);
                    geometryXMin = (geometryXMin < textVertex.x())
                        ? geometryXMin
                        : textVertex.x();
                    geometryXMax = (geometryXMax > textVertex.x())
                        ? geometryXMax
                        : textVertex.x();
                    geometryYMin = (geometryYMin < textVertex.y())
                        ? geometryYMin
                        : textVertex.y();
                    geometryYMax = (geometryYMax > textVertex.y())
                        ? geometryYMax
                        : textVertex.y();
                } else {
                    newGeometry.coord_index.push_back(-1);
                }
            }
        }

        //
        // Scale to maxExtent.
        //
        const float maxExtent =
            (this->max_extent_.sffloat::value() > 0.0)
            ? this->max_extent_.sffloat::value()
            : 0.0;
        if (maxExtent > 0.0) {
            const float currentMaxExtent = geometryXMax - geometryXMin;
            if (currentMaxExtent > maxExtent) {
                for (size_t i = 0; i < newGeometry.coord.size(); ++i) {
                    const vec3f & vertex = newGeometry.coord[i];
                    const vec3f scaledVertex(
                        vertex.x() / currentMaxExtent * maxExtent,
                        vertex.y(),
                        vertex.z()
                        );
                    newGeometry.coord[i] = scaledVertex;
                }
            }
        }

        //
        // Adjust for the minor alignment.
        //
        float xOffset = 0.0f, yOffset = 0.0f;
        if (justify[1] == "FIRST" || justify[1] == "") {
        } else if (justify[1] == "BEGIN") {
            if (horizontal) {
                yOffset = -(size * spacing);
            } else {
                xOffset = 0.0f;
            }
        } else if (justify[1] == "MIDDLE") {
            if (horizontal) {
                yOffset = ((size * spacing
                            * this->string_.mfstring::value().size()) / 2.0f)
                    - (size * spacing);
            } else {
                xOffset = ((size * spacing
                            * this->string_.mfstring::value().size()) / 2.0f)
                    - (size * spacing);
            }
        } else if (justify[1] == "END") {
            if (horizontal) {
                yOffset = size * spacing
                    * (this->string_.mfstring::value().size() - 1);
            } else {
                xOffset = size * spacing
                    * (this->string_.mfstring::value().size() - 1);
            }
        }
        for (size_t i = 0; i < newGeometry.coord.size(); ++i) {
            const vec3f & vertex = newGeometry.coord[i];
            const vec3f adjustedVertex(vertex.x() + xOffset,
                                       vertex.y() + yOffset,
                                       vertex.z());
            newGeometry.coord[i] = adjustedVertex;
        }

        //
        // Create the normals.
        //
        newGeometry.normal.resize(npolygons); // Throws std::bad_alloc.
        for (size_t i = 0; i < newGeometry.normal.size(); ++i) {
            static const vec3f normal(0.0, 0.0, 1.0);
            newGeometry.normal[i] = normal;
        }

        //
        // Create the texture coordinates.
        //
        newGeometry.tex_coord.resize(newGeometry.coord.size()); // std::bad_alloc
        for (size_t i = 0; i < newGeometry.tex_coord.size(); ++i) {
            const vec3f & vertex = newGeometry.coord[i];
            newGeometry.tex_coord[i] = vec2f(vertex.x() / size, vertex.y() / size);
        }

        this->text_geometry_ = newGeometry;
# endif // OPENVRML_ENABLE_RENDER_TEXT_NODE
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    texture_coordinate_class::
    texture_coordinate_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    texture_coordinate_class::~texture_coordinate_class()
        throw ()
    {}

   /**
    * @brief Create a node_type.
    *
    * @param id            the name for the new node_type.
    * @param interfaces    the interfaces for the new node_type.
    *
    * @return a boost::shared_ptr<node_type> to a node_type capable of creating
    *         TextureCoordinate nodes.
    *
    * @exception unsupported_interface if @p interfaces includes an interface
    *                                  not supported by
    *                                  texture_coordinate_class.
    * @exception std::bad_alloc        if memory allocation fails.
    */
    const boost::shared_ptr<openvrml::node_type>
    texture_coordinate_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        static const node_interface supportedInterface =
            node_interface(node_interface::exposedfield_id,
                           field_value::mfvec2f_id,
                           "point");

        typedef node_type_impl<texture_coordinate_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & textureCoordinateNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            if (*interface == supportedInterface) {
                textureCoordinateNodeType.add_exposedfield(
                    supportedInterface.field_type,
                    supportedInterface.id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<texture_coordinate_node>::
                        exposedfield<mfvec2f> >(
                            &texture_coordinate_node::point_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<texture_coordinate_node>::
                        exposedfield<mfvec2f> >(
                            &texture_coordinate_node::point_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<texture_coordinate_node>::
                        exposedfield<mfvec2f> >(
                            &texture_coordinate_node::point_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class texture_coordinate_node
     *
     * @brief TextureCoordinate node instances.
     */

    /**
     * @var texture_coordinate_node::texture_coordinate_class
     *
     * @brief Class object for TextureCoordinate instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<texture_coordinate_node>::exposedfield<openvrml::mfvec2f> texture_coordinate_node::point_
     *
     * @brief point exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    texture_coordinate_node::
    texture_coordinate_node(const node_type & type,
                            const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<texture_coordinate_node>(type, scope),
        openvrml::texture_coordinate_node(type, scope),
        point_(*this)
    {}

    /**
     * @brief Destroy.
     */
    texture_coordinate_node::~texture_coordinate_node()
        throw ()
    {}

    /**
     * @brief Get the points encapsulated by this node.
     *
     * @return the mfvec2f array of points for this node.
     */
    const std::vector<openvrml::vec2f> &
    texture_coordinate_node::point() const throw ()
    {
        return this->point_.mfvec2f::value();
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    texture_transform_class::
    texture_transform_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    texture_transform_class::~texture_transform_class()
        throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating TextureTransform nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  texture_transform_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    texture_transform_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 4> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec2f_id,
                           "center"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "rotation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec2f_id,
                           "scale"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec2f_id,
                           "translation")
        };

        typedef node_type_impl<texture_transform_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & textureTransformNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                textureTransformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::center_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::center_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::center_)));
            } else if (*interface == *++supported_interface) {
                textureTransformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sffloat> >(
                            &texture_transform_node::rotation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sffloat> >(
                            &texture_transform_node::rotation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sffloat> >(
                            &texture_transform_node::rotation_)));
            } else if (*interface == *++supported_interface) {
                textureTransformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::scale_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::scale_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::scale_)));
            } else if (*interface == *++supported_interface) {
                textureTransformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::translation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::translation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<texture_transform_node>::
                        exposedfield<sfvec2f> >(
                            &texture_transform_node::translation_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class texture_transform_node
     *
     * @brief TextureTransform node instances.
     */

    /**
     * @var texture_transform_node::texture_transform_class
     *
     * @brief Class object for TextureTransform instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<texture_transform_node>::exposedfield<openvrml::sfvec2f> texture_transform_node::center_
     *
     * @brief center exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<texture_transform_node>::exposedfield<openvrml::sffloat> texture_transform_node::rotation_
     *
     * @brief rotation exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<texture_transform_node>::exposedfield<openvrml::sfvec2f> texture_transform_node::scale_
     *
     * @brief scale exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<texture_transform_node>::exposedfield<openvrml::sfvec2f> texture_transform_node::translation_
     *
     * @brief translation exposedField.
     */

    /**
     * @brief Construct.
     *
     * @param type      the node_type associated with the instance.
     * @param scope         the scope that the new node will belong to.
     */
    texture_transform_node::
    texture_transform_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<texture_transform_node>(type, scope),
        openvrml::texture_transform_node(type, scope),
        center_(*this, vec2f(0.0, 0.0)),
        rotation_(*this, 0.0),
        scale_(*this, vec2f(1.0, 1.0)),
        translation_(*this, vec2f(0.0, 0.0))
    {}

    /**
     * @brief Destroy.
     */
    texture_transform_node::~texture_transform_node()
        throw ()
    {}

    /**
     * @brief render_texture_transform implementation.
     *
     * @param v viewer.
     */
    void
    texture_transform_node::
    do_render_texture_transform(viewer & v)
    {
        v.set_texture_transform(this->center_.sfvec2f::value(),
                                this->rotation_.sffloat::value(),
                                this->scale_.sfvec2f::value(),
                                this->translation_.sfvec2f::value());
    }


    /**
     * @brief Construct.
     *
     * @param browser   the browser associated with this node_class.
     */
    time_sensor_class::
    time_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    time_sensor_class::~time_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating TimeSensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by time_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    time_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 9> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "cycleInterval"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "loop"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "startTime"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sftime_id,
                           "stopTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "cycleTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sffloat_id,
                           "fraction_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "time")
        };

        typedef node_type_impl<time_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & timeSensorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                timeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        time_sensor_node::set_cycle_interval_listener>(
                            &time_sensor_node::set_cycle_interval_listener_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sftime>(
                            &time_sensor_node::cycle_interval_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sftime_emitter>(
                            &time_sensor_node::cycle_interval_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        time_sensor_node::enabled_exposedfield>(
                            &time_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        time_sensor_node::enabled_exposedfield>(
                            &time_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        time_sensor_node::enabled_exposedfield>(
                            &time_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sfbool> >(
                            &time_sensor_node::loop_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sfbool> >(
                            &time_sensor_node::loop_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sfbool> >(
                            &time_sensor_node::loop_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        time_sensor_node::set_start_time_listener>(
                            &time_sensor_node::set_start_time_listener_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sftime>(
                            &time_sensor_node::start_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sftime_emitter>(
                            &time_sensor_node::start_time_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sftime> >(
                            &time_sensor_node::stop_time_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sftime> >(
                            &time_sensor_node::stop_time_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::exposedfield<sftime> >(
                            &time_sensor_node::stop_time_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sftime_emitter>(
                            &time_sensor_node::cycle_time_emitter_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sffloat_emitter>(
                            &time_sensor_node::fraction_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sfbool_emitter>(
                            &time_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                timeSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<time_sensor_node>::sftime_emitter>(
                            &time_sensor_node::time_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class time_sensor_node
     *
     * @brief TimeSensor node instances.
     */

    /**
     * @var class time_sensor_node::time_sensor_class
     *
     * @brief Class object for TimeSensor nodes.
     */

    /**
     * @internal
     *
     * @class time_sensor_node::set_cycle_interval_listener
     *
     * @brief set_cycleInterval eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  time_sensor_node.
     */
    time_sensor_node::set_cycle_interval_listener::
    set_cycle_interval_listener(time_sensor_node & node):
        node_event_listener(node),
        event_listener_base<time_sensor_node>(node),
        sftime_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    time_sensor_node::set_cycle_interval_listener::
    ~set_cycle_interval_listener()
        throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param cycle_interval    cycleInterval.
     * @param timestamp         the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    time_sensor_node::set_cycle_interval_listener::
    do_process_event(const sftime & cycle_interval, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            time_sensor_node & node =
                dynamic_cast<time_sensor_node &>(this->node());

            if (!node.is_active_.value()) {
                node.cycle_interval_ = cycle_interval;
                node.lastTime = timestamp;
                node::emit_event(node.cycle_interval_changed_emitter_,
                                 timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

   /**
    * @internal
    *
    * @class time_sensor_node::enabled_exposedfield
    *
    * @brief enabled exposedField implementation.
    */
    
    /**
     * @brief Construct.
     *
     * @param node  time_sensor_node.
     */
    time_sensor_node::enabled_exposedfield::
    enabled_exposedfield(time_sensor_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfbool_listener(node),
        exposedfield<openvrml::sfbool>(node, true)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    time_sensor_node::enabled_exposedfield::
    enabled_exposedfield(const enabled_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfbool_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfbool>(obj)
    {}

    /**
     * @brief Destroy.
     */
    time_sensor_node::enabled_exposedfield::
    ~enabled_exposedfield()
        throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    time_sensor_node::enabled_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new enabled_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param enabled   enabled state.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    time_sensor_node::enabled_exposedfield::
    event_side_effect(const sfbool & enabled, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            time_sensor_node & node =
                dynamic_cast<time_sensor_node &>(this->node_event_listener::node());

            if (enabled.value() != node.is_active_.value()) {
                if (node.is_active_.value()) {
                    using openvrml_::fequal;

                    //
                    // Was active; shutdown.
                    //
                    double cycleInt = node.cycle_interval_.value();
                    double f = (cycleInt > 0.0)
                        ? fmod(node.time_.value() - node.start_time_.value(),
                               cycleInt)
                        : 0.0;

                    // Fraction of cycle message
                    node.fraction_changed_.value(float(fequal<double>()(f, 0.0)
                                                       ? 1.0
                                                       : (f / cycleInt)));
                } else {
                    //
                    // Was inactive; startup.
                    //
                    node.cycle_time_.value(timestamp);
                    node::emit_event(node.cycle_time_emitter_, timestamp);

                    // Fraction of cycle message
                    node.fraction_changed_.value(0.0);
                }
                node.time_.value(timestamp);
                node::emit_event(node.time_emitter_, timestamp);
                node::emit_event(node.fraction_changed_emitter_, timestamp);
                node.is_active_ = enabled;
                node::emit_event(node.is_active_emitter_, timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class time_sensor_node::set_start_time_listener
     *
     * @brief set_startTime eventIn handler.
     */

    /**
     * @brief Construct.
     *
     * @param node  time_sensor_node.
     */
    time_sensor_node::set_start_time_listener::
    set_start_time_listener(time_sensor_node & node):
        node_event_listener(node),
        event_listener_base<time_sensor_node>(node),
        sftime_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    time_sensor_node::set_start_time_listener::
    ~set_start_time_listener()
        throw ()
    {}

    /**
     * @brief Process event.
     *
     * @param start_time    startTime.
     * @param timestamp     the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    time_sensor_node::set_start_time_listener::
    do_process_event(const sftime & start_time, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            time_sensor_node & node =
                dynamic_cast<time_sensor_node &>(this->node());

            if (!node.is_active_.value()) {
                node.start_time_ = start_time;
                node.lastTime = timestamp;
                node::emit_event(node.start_time_changed_emitter_, timestamp);
            }
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var time_sensor_node::set_cycle_interval_listener time_sensor_node::set_cycle_interval_listener_
     *
     * @brief set_cycleInterval eventIn handler.
     */

    /**
     * @var openvrml::sftime time_sensor_node::cycle_interval_
     *
     * @brief cycleInterval exposedField value.
     */

    /**
     * @var openvrml::sftime_emitter time_sensor_node::cycle_interval_changed_emitter_
     *
     * @brief cycleInterval_changed event emitter.
     */

    /**
     * @var time_sensor_node::enabled_exposedfield time_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<time_sensor_node>::exposedfield<openvrml::sfbool> time_sensor_node::loop_
     *
     * @brief loop exposedField.
     */

    /**
     * @var time_sensor_node::set_start_time_listener time_sensor_node::set_start_time_listener_
     *
     * @brief set_startTime event handler.
     */

    /**
     * @var openvrml::sftime time_sensor_node::start_time_
     *
     * @brief startTime exposedField value.
     */

    /**
     * @var openvrml::sftime_emitter time_sensor_node::start_time_changed_emitter_
     *
     * @brief startTime_changed event emitter.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<time_sensor_node>::exposedfield<openvrml::sftime> time_sensor_node::stop_time_
     *
     * @brief stopTime exposedField.
     */

    /**
     * @var openvrml::sftime time_sensor_node::cycle_time_
     *
     * @brief cycleTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter time_sensor_node::cycle_time_emitter_
     *
     * @brief cycleTime eventOut emitter.
     */

    /**
     * @var openvrml::sffloat time_sensor_node::fraction_changed_
     *
     * @brief fraction_changed eventOut value.
     */

    /**
     * @var openvrml::sffloat_emitter time_sensor_node::fraction_changed_emitter_
     *
     * @brief fraction_changed eventOut emitter.
     */

/**
 * @var openvrml::sfbool time_sensor_node::is_active_
 *
 * @brief isActive eventOut value.
 */

/**
 * @var openvrml::sfbool_emitter time_sensor_node::is_active_emitter_
 *
 * @brief isActive eventOut emitter.
 */

/**
 * @var openvrml::sftime time_sensor_node::time_
 *
 * @brief time eventOut value.
 */

/**
 * @var openvrml::sftime_emitter time_sensor_node::time_emitter_
 *
 * @brief time eventOut emitter.
 */

/**
 * @var double time_sensor_node::lastTime
 *
 * @brief The timestamp previously received.
 */

/**
 * @brief Construct.
 *
 * @param type      the node_type associated with the instance.
 * @param scope         the scope that the new node will belong to.
 */
    time_sensor_node::
    time_sensor_node(const node_type & type,
                     const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<time_sensor_node>(type, scope),
        time_dependent_node(type, scope),
        child_node(type, scope),
        set_cycle_interval_listener_(*this),
        cycle_interval_(1.0),
        cycle_interval_changed_emitter_(*this, this->cycle_interval_),
        enabled_(*this),
        loop_(*this, false),
        set_start_time_listener_(*this),
        start_time_(0.0),
        start_time_changed_emitter_(*this, this->start_time_),
        stop_time_(*this, 0.0),
        cycle_time_emitter_(*this, this->cycle_time_),
        fraction_changed_emitter_(*this, this->fraction_changed_),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        time_emitter_(*this, this->time_),
        lastTime(-1.0)
    {}

/**
 * @brief Destroy.
 */
    time_sensor_node::~time_sensor_node() throw ()
    {}

/**
 * Generate timer events. If necessary, events prior to the timestamp (inTime)
 * are generated to respect stopTimes and cycleIntervals. The timestamp
 * should never be increased. This assumes the event loop delivers pending
 * events in order (ascending time stamps). Should inTime be modified?
 * Should ensure continuous events are delivered before discrete ones
 * (such as cycleTime, isActive).
 */
    void
    time_sensor_node::do_update(const double currentTime)
    {
        sftime timeNow(currentTime);

        if (this->enabled_.sfbool::value()) {
            if (this->lastTime > timeNow.value()) {
                this->lastTime = timeNow.value();
            }

            // Become active at startTime if either the valid stopTime hasn't
            // passed or we are looping.
            if (!this->is_active_.value()
                && this->start_time_.value() <= timeNow.value()
                && this->start_time_.value() >= this->lastTime
                && ((this->stop_time_.sftime::value() < this->start_time_.value()
                     || this->stop_time_.sftime::value() > timeNow.value())
                    || this->loop_.sfbool::value())) {

                // Start at first tick >= startTime
                this->is_active_.value(true);
                node::emit_event(this->is_active_emitter_, timeNow.value());
                this->time_.value(timeNow.value());
                node::emit_event(this->time_emitter_, timeNow.value());
                this->fraction_changed_.value(0.0);
                node::emit_event(this->fraction_changed_emitter_,
                                 timeNow.value());
                this->cycle_time_.value(timeNow.value());
                node::emit_event(this->cycle_time_emitter_, timeNow.value());
            }

            // Running (active and enabled)
            else if (this->is_active_.value()) {
                using openvrml_::fequal;
                using openvrml_::fless_equal;

                double f, cycleInt = this->cycle_interval_.value();
                bool deactivate = false;

                // Are we done? Choose min of stopTime or start + single cycle.
                if ((this->stop_time_.sftime::value() > this->start_time_.value()
                     && fless_equal<double>()(this->stop_time_.sftime::value(),
                                              timeNow.value()))
                    || (!this->loop_.sfbool::value()
                        && fless_equal<double>()(this->start_time_.value()
                                                 + cycleInt,
                                                 timeNow.value()))) {
                    this->is_active_.value(false);

                    // Must respect stopTime/cycleInterval exactly
                    if (this->start_time_.value() + cycleInt
                        < this->stop_time_.sftime::value()) {
                        timeNow = sftime(this->start_time_.value() + cycleInt);
                    } else {
                        timeNow = this->stop_time_;
                    }

                    deactivate = true;
                }

                f = (cycleInt > 0.0 && timeNow.value() > this->start_time_.value())
                    ? fmod(timeNow.value() - this->start_time_.value(),
                           cycleInt)
                    : 0.0;

                fequal<double> feq;

                // Fraction of cycle message
                this->fraction_changed_.value(feq(f, 0.0)
                                              ? 1.0f
                                              : float(f / cycleInt));
                node::emit_event(this->fraction_changed_emitter_,
                                 timeNow.value());

                // Current time message
                this->time_.value(timeNow.value());
                node::emit_event(this->time_emitter_, timeNow.value());

                // End of cycle message (this may miss cycles...)
                if (feq(this->fraction_changed_.value(), 1.0)) {
                    this->cycle_time_.value(timeNow.value());
                    node::emit_event(this->cycle_time_emitter_,
                                     timeNow.value());
                }

                if (deactivate) {
                    node::emit_event(this->is_active_emitter_,
                                     timeNow.value());
                }
            }

            // Tell the scene this node needs quick updates while it is active.
            // Should check whether time, fraction_changed eventOuts are
            // being used, and set delta to cycleTime if not...
            if (this->is_active_.value()) {
                this->type().node_class().browser().delta(0.0);
            }
            this->lastTime = currentTime;
        }
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    time_sensor_node::do_initialize(double)
        throw (std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_time_dependent(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    time_sensor_node::do_shutdown(double)
        throw ()
    {
        assert(this->scene());
        this->scene()->browser().remove_time_dependent(*this);
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    touch_sensor_class::
    touch_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    touch_sensor_class::~touch_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating TouchSensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by touch_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    touch_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 7> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "hitNormal_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec3f_id,
                           "hitPoint_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfvec2f_id,
                           "hitTexCoord_changed"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isOver"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "touchTime")
        };

        typedef node_type_impl<touch_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & touchSensorNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                touchSensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<touch_sensor_node>::exposedfield<sfbool> >(
                            &touch_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<touch_sensor_node>::exposedfield<sfbool> >(
                            &touch_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::exposedfield<sfbool> >(
                            &touch_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sfvec3f_emitter>(
                            &touch_sensor_node::hit_normal_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sfvec3f_emitter>(
                            &touch_sensor_node::hit_point_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sfvec2f_emitter>(
                            &touch_sensor_node::hit_tex_coord_changed_emitter_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sfbool_emitter>(
                            &touch_sensor_node::is_active_emitter_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sfbool_emitter>(
                            &touch_sensor_node::is_over_emitter_)));
            } else if (*interface == *++supported_interface) {
                touchSensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<touch_sensor_node>::sftime_emitter>(
                            &touch_sensor_node::touch_time_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class touch_sensor_node
     *
     * @brief TouchSensor node instances.
     */

    /**
     * @var touch_sensor_node::touch_sensor_class
     *
     * @brief Class object for TouchSensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<touch_sensor_node>::exposedfield<openvrml::sfbool> touch_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::sfvec3f touch_sensor_node::hit_normal_changed_
     *
     * @brief hitNormal_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter touch_sensor_node::hit_normal_changed_emitter_
     *
     * @brief hitNormal_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec3f touch_sensor_node::hit_point_changed_
     *
     * @brief hitPoint_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec3f_emitter touch_sensor_node::hit_point_changed_emitter_
     *
     * @brief hitPoint_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfvec2f touch_sensor_node::hit_tex_coord_changed_
     *
     * @brief hitTexCoord_changed eventOut value.
     */

    /**
     * @var openvrml::sfvec2f_emitter touch_sensor_node::hit_tex_coord_changed_emitter_
     *
     * @brief hitTexCoord_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfbool touch_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter touch_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sfbool touch_sensor_node::is_over_
     *
     * @brief isOver eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter touch_sensor_node::is_over_emitter_
     *
     * @brief isOver eventOut emitter.
     */

    /**
     * @var openvrml::sftime touch_sensor_node::touch_time_
     *
     * @brief touchTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter touch_sensor_node::touch_time_emitter_
     *
     * @brief touchTime eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    touch_sensor_node::
    touch_sensor_node(const node_type & type,
                      const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<touch_sensor_node>(type, scope),
        pointing_device_sensor_node(type, scope),
        enabled_(*this, true),
        hit_normal_changed_emitter_(*this, this->hit_normal_changed_),
        hit_point_changed_emitter_(*this, this->hit_point_changed_),
        hit_tex_coord_changed_emitter_(*this, this->hit_tex_coord_changed_),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        is_over_(false),
        is_over_emitter_(*this, this->is_over_),
        touch_time_(0.0),
        touch_time_emitter_(*this, this->touch_time_)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    touch_sensor_node::~touch_sensor_node() throw ()
    {}

    /**
     * @todo Doesn't compute the xxx_changed eventOuts yet...
     */
    void touch_sensor_node::do_activate(double timestamp,
                                        const bool over,
                                        const bool active,
                                        const double (&)[3])
    {
        if (this->enabled_.sfbool::value()) {
            if (over && !active && this->is_active_.value()) {
                this->touch_time_.value(timestamp);
                node::emit_event(this->touch_time_emitter_, timestamp);
            }

            if (over != this->is_over_.value()) {
                this->is_over_.value(over);
                node::emit_event(this->is_over_emitter_, timestamp);
            }

            if (active != this->is_active_.value()) {
                this->is_active_.value(active);
                node::emit_event(this->is_active_emitter_, timestamp);
            }
            // if (over && any routes from eventOuts)
            //   generate xxx_changed eventOuts...
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    transform_class::
    transform_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    transform_class::~transform_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Transform nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by transform_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    transform_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 10> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "addChildren"),
            node_interface(node_interface::eventin_id,
                           field_value::mfnode_id,
                           "removeChildren"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "center"),
            node_interface(node_interface::exposedfield_id,
                           field_value::mfnode_id,
                           "children"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfrotation_id,
                           "rotation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "scale"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfrotation_id,
                           "scaleOrientation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "translation"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxCenter"),
            node_interface(node_interface::field_id,
                           field_value::sfvec3f_id,
                           "bboxSize")
        };

        typedef node_type_impl< ::transform_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & transformNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                transformNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::add_children_listener>(
                            &::transform_node::add_children_listener_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::remove_children_listener>(
                            &::transform_node::remove_children_listener_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::center_exposedfield>(
                            &::transform_node::center_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::center_exposedfield>(
                            &::transform_node::center_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::center_exposedfield>(
                            &::transform_node::center_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::children_exposedfield>(
                            &::transform_node::children_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::children_exposedfield>(
                            &::transform_node::children_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::children_exposedfield>(
                            &::transform_node::children_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::rotation_exposedfield>(
                            &::transform_node::rotation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::rotation_exposedfield>(
                            &::transform_node::rotation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::rotation_exposedfield>(
                            &::transform_node::rotation_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::scale_exposedfield>(
                            &::transform_node::scale_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::scale_exposedfield>(
                            &::transform_node::scale_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::scale_exposedfield>(
                            &::transform_node::scale_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::scale_orientation_exposedfield>(
                            &::transform_node::scale_orientation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::scale_orientation_exposedfield>(
                            &::transform_node::scale_orientation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::scale_orientation_exposedfield>(
                            &::transform_node::scale_orientation_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        ::transform_node::translation_exposedfield>(
                            &::transform_node::translation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        ::transform_node::translation_exposedfield>(
                            &::transform_node::translation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        ::transform_node::translation_exposedfield>(
                            &::transform_node::translation_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &::transform_node::bbox_center_)));
            } else if (*interface == *++supported_interface) {
                transformNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfvec3f>(
                            &::transform_node::bbox_size_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }


    /**
     * @class transform_node
     *
     * @brief Transform node instances.
     */

    /**
     * @var class transform_node::transform_class
     *
     * @brief Class object for Transform nodes.
     */

    /**
     * @internal
     *
     * @class transform_node::center_exposedfield
     *
     * @brief center exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  transform_node.
     */
    transform_node::center_exposedfield::
    center_exposedfield(transform_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(node),
        exposedfield<openvrml::sfvec3f>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    transform_node::center_exposedfield::
    center_exposedfield(const center_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfvec3f>(obj)
    {}

    /**
     * @brief Destroy.
     */
    transform_node::center_exposedfield::~center_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    transform_node::center_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new center_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param center    center.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    transform_node::center_exposedfield::event_side_effect(const sfvec3f &,
                                                           double)
        throw (std::bad_alloc)
    {
        try {
            transform_node & node =
                dynamic_cast<transform_node &>(this->node_event_listener::node());
            node.bounding_volume_dirty(true);
            node.transform_dirty = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class transform_node::rotation_exposedfield
     *
     * @brief rotation exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  transform_node.
     */
    transform_node::rotation_exposedfield::
    rotation_exposedfield(transform_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(node),
        exposedfield<openvrml::sfrotation>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    transform_node::rotation_exposedfield::
    rotation_exposedfield(const rotation_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfrotation>(obj)
    {}

    /**
     * @brief Destroy.
     */
    transform_node::rotation_exposedfield::~rotation_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    transform_node::rotation_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new rotation_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param rotation  rotation.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    transform_node::rotation_exposedfield::
    event_side_effect(const sfrotation &, double)
        throw (std::bad_alloc)
    {
        try {
            transform_node & node =
                dynamic_cast<transform_node &>(this->node_event_listener::node());
            node.bounding_volume_dirty(true);
            node.transform_dirty = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class transform_node::scale_exposedfield
     *
     * @brief scale exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  transform_node.
     */
    transform_node::scale_exposedfield::
    scale_exposedfield(transform_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(node),
        exposedfield<openvrml::sfvec3f>(node, vec3f(1.0f, 1.0f, 1.0f))
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    transform_node::scale_exposedfield::
    scale_exposedfield(const scale_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfvec3f>(obj)
    {}

    /**
     * @brief Destroy.
     */
    transform_node::scale_exposedfield::
    ~scale_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    transform_node::scale_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new scale_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param scale     scale.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    transform_node::scale_exposedfield::event_side_effect(const sfvec3f &,
                                                          double)
        throw (std::bad_alloc)
    {
        try {
            transform_node & node =
                dynamic_cast<transform_node &>(this->node_event_listener::node());
            node.bounding_volume_dirty(true);
            node.transform_dirty = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class transform_node::scale_orientation_exposedfield
     *
     * @brief scaleOrientation exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  transform_node.
     */
    transform_node::scale_orientation_exposedfield::
    scale_orientation_exposedfield(transform_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(node),
        exposedfield<openvrml::sfrotation>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    transform_node::scale_orientation_exposedfield::
    scale_orientation_exposedfield(const scale_orientation_exposedfield & obj)
        throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfrotation>(obj)
    {}

    /**
     * @brief Destroy.
     */
    transform_node::scale_orientation_exposedfield::
    ~scale_orientation_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    transform_node::scale_orientation_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new scale_orientation_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param scale_orientation scaleOrientation.
     * @param timestamp         the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    transform_node::scale_orientation_exposedfield::
    event_side_effect(const sfrotation &, double) throw (std::bad_alloc)
    {
        try {
            transform_node & node =
                dynamic_cast<transform_node &>(this->node_event_listener::node());
            node.bounding_volume_dirty(true);
            node.transform_dirty = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @internal
     *
     * @class transform_node::translation_exposedfield
     *
     * @brief translation exposedField implementation.
     */

    /**
     * @brief Construct.
     *
     * @param node  transform_node.
     */
    transform_node::translation_exposedfield::
    translation_exposedfield(transform_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(node),
        exposedfield<openvrml::sfvec3f>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    transform_node::translation_exposedfield::
    translation_exposedfield(const translation_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfvec3f>(obj)
    {}

    /**
     * @brief Destroy.
     */
    transform_node::translation_exposedfield::
    ~translation_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    transform_node::translation_exposedfield::do_clone() const
        throw (std::bad_alloc)
    {
        return std::auto_ptr<openvrml::field_value>(
            new translation_exposedfield(*this));
    }

    /**
     * @brief Process event.
     *
     * @param translation     translation.
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    transform_node::translation_exposedfield::
    event_side_effect(const sfvec3f &, double)
        throw (std::bad_alloc)
    {
        try {
            transform_node & node =
                dynamic_cast<transform_node &>(this->node_event_listener::node());
            node.bounding_volume_dirty(true);
            node.transform_dirty = true;
        } catch (std::bad_cast & ex) {
            OPENVRML_PRINT_EXCEPTION_(ex);
        }
    }

    /**
     * @var transform_node::center_exposedfield transform_node::center_
     *
     * @brief center exposedField.
     */

    /**
     * @var transform_node::rotation_exposedfield transform_node::rotation_
     *
     * @brief rotation exposedField.
     */

    /**
     * @var transform_node::scale_exposedfield transform_node::scale_
     *
     * @brief scale exposedField.
     */

    /**
     * @var transform_node::scale_orientation_exposedfield transform_node::scale_orientation_
     *
     * @brief scaleOrientation exposedField.
     */

    /**
     * @var transform_node::translation_exposedfield transform_node::translation_
     *
     * @brief translation exposedField.
     */

    /**
     * @var openvrml::viewer::object_t transform_node::xformObject
     *
     * @brief A handle to the renderer's representation of the Transform.
     */

    /**
     * @var openvrml::mat4f transform_node::transform_
     *
     * @brief Cached copy of this node's transformation.
     */

    /**
     * @var bool transform_node::transform_dirty
     *
     * @brief Flag to indicate whether @a transform_ needs to be updated.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    transform_node::
    transform_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        grouping_node(type, scope),
        grouping_node_base<transform_node>(type, scope),
        openvrml::transform_node(type, scope),
        center_(*this),
        rotation_(*this),
        scale_(*this),
        scale_orientation_(*this),
        translation_(*this),
        transform_dirty(true),
        xformObject(0)
    {
        this->bounding_volume_dirty(true);
    }

    /**
     * @brief Destroy.
     */
    transform_node::~transform_node() throw ()
    {
        // delete xformObject...
    }

    /**
     * @brief Get the transformation associated with the node as a matrix.
     *
     * @return the transformation associated with the node.
     */
    const openvrml::mat4f &
    transform_node::transform() const throw ()
    {
        this->update_transform();
        return this->transform_;
    }

    /**
     * @brief Render the node.
     *
     * @param viewer    a Viewer.
     * @param context   the rendering context.
     */
    void
    transform_node::
    do_render_child(openvrml::viewer & viewer, rendering_context context)
    {
        if (context.cull_flag != bounding_volume::inside) {
            assert(dynamic_cast<const bounding_sphere *>
                   (&this->bounding_volume()));
            const bounding_sphere & bs =
                static_cast<const bounding_sphere &>(this->bounding_volume());
            bounding_sphere bv_copy(bs);
            bv_copy.transform(context.matrix());
            bounding_volume::intersection r =
                viewer.intersect_view_volume(bv_copy);
            if (context.draw_bounding_spheres) {
                viewer.draw_bounding_sphere(bs, r);
            }

            if (r == bounding_volume::outside) { return; }
            if (r == bounding_volume::inside) {
                context.cull_flag = bounding_volume::inside;
            }
        }

        mat4f new_LM = this->transform_ * context.matrix();
        context.matrix(new_LM);

        if (this->xformObject && modified()) {
            viewer.remove_object(this->xformObject);
            this->xformObject = 0;
        }

        if (this->xformObject) {
            viewer.insert_reference(this->xformObject);
        } else if (!this->children_.mfnode::value().empty()) {
            this->xformObject = viewer.begin_object(this->id().c_str());

            // Apply transforms
            viewer.transform(this->transform());
            // Render children
            this->grouping_node_base<transform_node>::render_nocull(viewer,
                                                                    context);

            viewer.end_object();
        }
        this->node::modified(false);
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    transform_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            const_cast<transform_node *>(this)->recalc_bsphere();
        }
        return this->bsphere;
    }

    /**
     * @brief Recalculate the bounding volume.
     */
    void transform_node::recalc_bsphere()
    {
        this->bsphere = bounding_sphere();
        for (size_t i = 0; i < this->children_.mfnode::value().size(); ++i) {
            const boost::intrusive_ptr<node> & node = this->children_.mfnode::value()[i];
            bounded_volume_node * bounded_volume =
                node_cast<bounded_volume_node *>(node.get());
            if (bounded_volume) {
                const openvrml::bounding_volume & ci_bv =
                    bounded_volume->bounding_volume();
                this->bsphere.extend(ci_bv);
            }
        }
        this->bsphere.transform(this->transform());
        this->bounding_volume_dirty(false);
    }

    /**
     * @brief Update @a transform.
     *
     * If @a transform_dirty is @c true, resynchronize the cached matrix
     * @a transform with the node fields; otherwise do nothing.
     *
     * @note P' = T � C � R � SR � S � -SR � -C � P
     */
    void transform_node::update_transform() const throw ()
    {
        if (this->transform_dirty) {
            this->transform_ =
                mat4f::transformation(
                    this->translation_.sfvec3f::value(),
                    this->rotation_.sfrotation::value(),
                    this->scale_.sfvec3f::value(),
                    this->scale_orientation_.sfrotation::value(),
                    this->center_.sfvec3f::value());
            this->transform_dirty = false;
        }
    }


    /**
     * @typedef viewpoint_class::bound_nodes_t
     *
     * @brief A stack of bound Viewpoint nodes.
     */

    /**
     * @var viewpoint_node * viewpoint_class::first
     *
     * @brief The first Viewpoint node in the initial scene graph.
     */

    /**
     * @var viewpoint_class::bound_nodes_t viewpoint_class::bound_nodes
     *
     * @brief The stack of bound Viewpoint nodes.
     */

    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    viewpoint_class::
    viewpoint_class(openvrml::browser & browser):
        node_class(browser),
        first(0)
    {}

    /**
     * @brief Destroy.
     */
    viewpoint_class::~viewpoint_class() throw ()
    {}

    /**
     * @brief Set the first Viewpoint node in the world.
     *
     * The first Viewpoint node in the world is used as the initial viewpoint.
     * This function is used by <code>viewpoint_node::do_initialize</code>.
     *
     * @param viewpoint    a Viewpoint node.
     */
    void
    viewpoint_class::set_first(viewpoint_node & viewpoint)
        throw ()
    {
        assert(!this->has_first());
        this->first = &viewpoint;
    }

    /**
     * @brief Reset the pointer to the first Viewpoint node in the world to
     *        null.
     *
     * This function is called by <code>viewpoint_node::do_shutdown</code>.
     */
    void viewpoint_class::reset_first() throw ()
    {
        this->first = 0;
    }

    /**
     * @brief Check to see if the first node has been set.
     *
     * This method is used by viewpoint_node::do_initialize.
     *
     * @return @c true if the first node has already been set; @c false
     *         otherwise.
     */
    bool viewpoint_class::has_first() const throw ()
    {
        return this->first;
    }

    /**
     * @brief Check to see if a node is registered as the "first" node.
     *
     * @param viewpoint a viewpoint_node.
     *
     * @return @c true if @p viewpoint is the fist node; @c false otherwise.
     */
    bool
    viewpoint_class::is_first(viewpoint_node & viewpoint)
        throw ()
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
    void
    viewpoint_class::bind(viewpoint_node & viewpoint, const double timestamp)
        throw (std::bad_alloc)
    {
        //
        // If the node is already the active node, do nothing.
        //
        if (!this->bound_nodes.empty()
            && &viewpoint == this->bound_nodes.back()) {
            return;
        }

        //
        // If the node is already on the stack, remove it.
        //
        const bound_nodes_t::iterator pos =
            std::find(this->bound_nodes.begin(), this->bound_nodes.end(),
                      &viewpoint);
        if (pos != this->bound_nodes.end()) { this->bound_nodes.erase(pos); }

        //
        // Send FALSE from the currently active node's isBound.
        //
        if (!this->bound_nodes.empty()) {
            viewpoint_node & current =
                dynamic_cast<viewpoint_node &>(*this->bound_nodes.back());
            current.is_bound_.value(false);
            node::emit_event(current.is_bound_emitter_, timestamp);
        }

        //
        // Push the node to the top of the stack, and have it send isBound
        // TRUE.
        //
        this->bound_nodes.push_back(&viewpoint);
        viewpoint.is_bound_.value(true);
        node::emit_event(viewpoint.is_bound_emitter_, timestamp);

        this->browser().active_viewpoint(viewpoint);
    }

    /**
     * @brief Remove a Viewpoint from the bound node stack.
     *
     * @param viewpoint    the node to unbind.
     * @param timestamp    the current time.
     */
    void viewpoint_class::unbind(viewpoint_node & viewpoint,
                                 const double timestamp)
        throw ()
    {
        const bound_nodes_t::iterator pos =
            std::find(this->bound_nodes.begin(), this->bound_nodes.end(),
                      &viewpoint);
        if (pos != this->bound_nodes.end()) {
            viewpoint.is_bound_.value(false);
            node::emit_event(viewpoint.is_bound_emitter_, timestamp);

            if (pos == this->bound_nodes.end() - 1
                && this->bound_nodes.size() > 1) {
                viewpoint_node & newActive =
                    dynamic_cast<viewpoint_node &>(
                        **(this->bound_nodes.end() - 2));
                newActive.is_bound_.value(true);
                node::emit_event(newActive.is_bound_emitter_, timestamp);

                this->browser().active_viewpoint(viewpoint);
            } else {
                this->browser().reset_default_viewpoint();
            }
            this->bound_nodes.erase(pos);
        }
    }

    /**
     * @brief node_class-specific initialization.
     *
     * @param initial_viewpoint the viewpoint_node that should be bound
     *                          initially.
     * @param timestamp         the current time.
     */
    void
    viewpoint_class::
    do_initialize(openvrml::viewpoint_node * initial_viewpoint,
                  const double timestamp)
        throw ()
    {
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

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating Viewpoint nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by viewpoint_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    viewpoint_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 8> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::eventin_id,
                           field_value::sfbool_id,
                           "set_bind"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sffloat_id,
                           "fieldOfView"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "jump"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfrotation_id,
                           "orientation"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "position"),
            node_interface(node_interface::field_id,
                           field_value::sfstring_id,
                           "description"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "bindTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isBound")
        };

        typedef node_type_impl< ::viewpoint_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & viewpointNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                viewpointNodeType.add_eventin(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        viewpoint_node::set_bind_listener>(
                            &viewpoint_node::set_bind_listener_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sffloat> >(
                            &viewpoint_node::field_of_view_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sffloat> >(
                            &viewpoint_node::field_of_view_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sffloat> >(
                            &viewpoint_node::field_of_view_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sfbool> >(
                            &viewpoint_node::jump_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sfbool> >(
                            &viewpoint_node::jump_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<viewpoint_node>::exposedfield<sfbool> >(
                            &viewpoint_node::jump_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        viewpoint_node::orientation_exposedfield>(
                            &viewpoint_node::orientation_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        viewpoint_node::orientation_exposedfield>(
                            &viewpoint_node::orientation_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        viewpoint_node::orientation_exposedfield>(
                            &viewpoint_node::orientation_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        viewpoint_node::position_exposedfield>(
                            &viewpoint_node::position_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        viewpoint_node::position_exposedfield>(
                            &viewpoint_node::position_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        viewpoint_node::position_exposedfield>(
                            &viewpoint_node::position_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfstring>(
                            &viewpoint_node::description_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<viewpoint_node>::sftime_emitter>(
                            &viewpoint_node::bind_time_emitter_)));
            } else if (*interface == *++supported_interface) {
                viewpointNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<viewpoint_node>::sfbool_emitter>(
                            &viewpoint_node::is_bound_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class viewpoint_node
     *
     * @brief Viewpoint node instance.
     */

    /**
     * @var class viewpoint_node::viewpoint_class
     *
     * @brief Class object for Viewpoint nodes.
     */

    /**
     * @internal
     *
     * @class viewpoint_node::set_bind_listener
     *
     * @brief set_bind eventIn listener.
     */

    /**
     * @brief Construct.
     *
     * @param node viewpoint_node.
     */
    viewpoint_node::set_bind_listener::
    set_bind_listener(viewpoint_node & node):
        node_event_listener(node),
        event_listener_base<viewpoint_node>(node),
        sfbool_listener(node)
    {}

    /**
     * @brief Destroy.
     */
    viewpoint_node::set_bind_listener::~set_bind_listener() throw ()
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
    viewpoint_node::set_bind_listener::
    do_process_event(const sfbool & value, const double timestamp)
        throw (std::bad_alloc)
    {
        try {
            viewpoint_node & node =
                dynamic_cast<viewpoint_node &>(this->node());
            viewpoint_class & node_class =
                const_cast<viewpoint_class &>(
                    static_cast<const viewpoint_class &>(
                        node.type().node_class()));
            if (value.value()) {
                node_class.bind(node, timestamp);
            } else {
                node_class.unbind(node, timestamp);
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
    viewpoint_node::orientation_exposedfield::
    orientation_exposedfield(viewpoint_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(node),
        exposedfield<openvrml::sfrotation>(node)
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    viewpoint_node::orientation_exposedfield::
    orientation_exposedfield(const orientation_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfrotation_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfrotation>(obj)
    {}

    /**
     * @brief Destroy.
     */
    viewpoint_node::orientation_exposedfield::
    ~orientation_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    viewpoint_node::orientation_exposedfield::do_clone() const
        throw (std::bad_alloc)
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
    viewpoint_node::orientation_exposedfield::
    event_side_effect(const sfrotation &, double)
        throw (std::bad_alloc)
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
    viewpoint_node::position_exposedfield::
    position_exposedfield(viewpoint_node & node):
        node_event_listener(node),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(node),
        exposedfield<openvrml::sfvec3f>(node, vec3f(0.0f, 0.0f, 10.0f))
    {}

    /**
     * @brief Construct a copy.
     *
     * @param obj   instance to copy.
     */
    viewpoint_node::position_exposedfield::
    position_exposedfield(const position_exposedfield & obj) throw ():
        openvrml::event_listener(),
        node_event_listener(obj.node_event_listener::node()),
        openvrml::event_emitter(static_cast<const field_value &>(*this)),
        sfvec3f_listener(obj.node_event_listener::node()),
        exposedfield<openvrml::sfvec3f>(obj)
    {}

    /**
     * @brief Destroy.
     */
    viewpoint_node::position_exposedfield::~position_exposedfield() throw ()
    {}

    /**
     * @brief Polymorphically construct a copy.
     *
     * @return a copy of the instance.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    std::auto_ptr<openvrml::field_value>
    viewpoint_node::position_exposedfield::do_clone() const
        throw (std::bad_alloc)
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
    viewpoint_node::position_exposedfield::event_side_effect(const sfvec3f &,
                                                             double)
        throw (std::bad_alloc)
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
     * @var viewpoint_node::set_bind_listener viewpoint_node::set_bind_listener_
     *
     * @brief set_bind eventIn handler.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<viewpoint_node>::exposedfield<openvrml::sffloat> viewpoint_node::field_of_view_
     *
     * @brief fieldOfView exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<viewpoint_node>::exposedfield<openvrml::sfbool> viewpoint_node::jump_
     *
     * @brief jump exposedField.
     */

    /**
     * @var viewpoint_node::orientation_exposedfield viewpoint_node::orientation_
     *
     * @brief orientation exposedField.
     */

    /**
     * @var viewpoint_node::position_exposedfield viewpoint_node::position_
     *
     * @brief position exposedField.
     */

    /**
     * @var openvrml::sfstring viewpoint_node::description_
     *
     * @brief description field.
     */

    /**
     * @var openvrml::sfbool viewpoint_node::is_bound_
     *
     * @brief isBound eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter viewpoint_node::is_bound_emitter_
     *
     * @brief isBound eventOut emitter.
     */

    /**
     * @var openvrml::sftime viewpoint_node::bind_time_
     *
     * @brief bindTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter viewpoint_node::bind_time_emitter_
     *
     * @brief bindTime eventOut emitter.
     */

    /**
     * @var openvrml::mat4f viewpoint_node::parent_transform
     *
     * @brief The accumulated transformation applied by any parent nodes.
     */

    /**
     * @var openvrml::mat4f viewpoint_node::final_transformation
     *
     * @brief The product of @a parent_transform and any transformation applied
     *        by the Viewpoint node.
     */

    /**
     * @var bool viewpoint_node::final_transformation_dirty
     *
     * @brief Flag that indicates if @a final_transformation needs to be
     *        updated.
     */

    /**
     * @var mat4f viewpoint_node::user_view_transform_
     *
     * @brief The transformation applied to the user view.
     *
     * Generally the result of any user navigation.
     */

    const float DEFAULT_FIELD_OF_VIEW = 0.785398f;

    /**
     * @brief Construct.
     *
     * @param type      the node_type associated with the instance.
     * @param scope         the scope that the new node will belong to.
     */
    viewpoint_node::
    viewpoint_node(const node_type & type,
                   const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        child_node(type, scope),
        abstract_node<viewpoint_node>(type, scope),
        openvrml::viewpoint_node(type, scope),
        set_bind_listener_(*this),
        field_of_view_(*this, DEFAULT_FIELD_OF_VIEW),
        jump_(*this, true),
        orientation_(*this),
        position_(*this),
        is_bound_emitter_(*this, this->is_bound_),
        bind_time_emitter_(*this, this->bind_time_),
        final_transformation_dirty(true)
    {}

    /**
     * @brief Destroy.
     */
    viewpoint_node::~viewpoint_node() throw ()
    {}

    /**
     * @brief Get the transformation of the viewpoint_node in the global
     *        coordinate system.
     *
     * @return the transformation of the viewpoint_node in the global
     *         coordinate system.
     */
    const openvrml::mat4f & viewpoint_node::transformation() const throw ()
    {
        this->update_final_transformation();
        return this->final_transformation;
    }

    /**
     * @brief Get the transformation of the user view relative to the
     *      viewpoint_node.
     *
     * @return the transformation of the user view relative to the
     *         viewpoint_node.
     */
    const openvrml::mat4f & viewpoint_node::user_view_transform() const
        throw ()
    {
        return this->user_view_transform_;
    }

   /**
    * @brief Set the transformation of the user view relative to the
    *        viewpoint_node.
    *
    * @param transform the new transformation.
    */
    void
    viewpoint_node::user_view_transform(const mat4f & transform) throw ()
    {
        this->user_view_transform_ = transform;
    }

    /**
     * @brief description accessor.
     *
     * @return the description.
     */
    const std::string & viewpoint_node::description() const throw ()
    {
        return this->description_.value();
    }

    /**
     * @brief Get the field of view.
     *
     * @return the field of view in radians.
     */
    float viewpoint_node::field_of_view() const throw ()
    {
        return this->field_of_view_.sffloat::value();
    }

    /**
     * @brief orientation accessor.
     *
     * @return the orientation.
     */
    const openvrml::sfrotation & viewpoint_node::orientation() const
    {
        return this->orientation_;
    }

    /**
     * @brief position accessor.
     *
     * @return the position.
     */
    const openvrml::sfvec3f & viewpoint_node::position() const
    {
        return this->position_;
    }

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     */
    void
    viewpoint_node::do_initialize(double)
        throw ()
    {
        assert(this->scene());
        this->scene()->browser().add_viewpoint(*this);
        assert(dynamic_cast<const viewpoint_class *>(
                   &this->type().node_class()));
        viewpoint_class & nodeClass =
            const_cast<viewpoint_class &>(
                static_cast<const viewpoint_class &>(
                    this->type().node_class()));
        if (!nodeClass.has_first()) { nodeClass.set_first(*this); }
    }

    struct OPENVRML_LOCAL accumulate_transform_ :
        std::unary_function<openvrml::node *, void> {

        explicit accumulate_transform_(openvrml::mat4f & transform) throw ():
            transform(&transform)
        {}

        void operator()(openvrml::node * node) const throw ()
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
    void viewpoint_node::do_relocate() throw (std::bad_alloc)
    {
        assert(this->scene());
        const node_path path = this->scene()->browser().find_node(*this);
        assert(!path.empty());
        this->parent_transform = mat4f();
        std::for_each(path.begin(), path.end(),
                      accumulate_transform_(this->parent_transform));
        this->final_transformation_dirty = true;
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void viewpoint_node::do_shutdown(const double timestamp) throw ()
    {
        viewpoint_class & node_class =
            const_cast<viewpoint_class &>(
                static_cast<const viewpoint_class &>(
                    this->type().node_class()));
        node_class.unbind(*this, timestamp);
        assert(this->scene());
        this->scene()->browser().remove_viewpoint(*this);

        if (node_class.is_first(*this)) { node_class.reset_first(); }
    }

    /**
     * @brief Update @a final_transformation.
     *
     * If @a final_transformation_dirty is @c true, update
     * @a final_transformation and sets @a final_transformation_dirty to
     * @c false; otherwise, do nothing.
     */
    void viewpoint_node::update_final_transformation() const throw ()
    {
        if (this->final_transformation_dirty) {
            static const vec3f scale(1.0, 1.0, 1.0);
            static const rotation scaleOrientation;
            static const vec3f center;
            const mat4f & t =
                mat4f::transformation(this->position_.sfvec3f::value(),
                                      this->orientation_.sfrotation::value(),
                                      scale,
                                      scaleOrientation,
                                      center);
            this->final_transformation = t * this->parent_transform;
            this->final_transformation_dirty = false;
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    visibility_sensor_class::
    visibility_sensor_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    visibility_sensor_class::~visibility_sensor_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating VisibilitySensor nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by
     *                                  visibility_sensor_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    visibility_sensor_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 6> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "center"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfbool_id,
                           "enabled"),
            node_interface(node_interface::exposedfield_id,
                           field_value::sfvec3f_id,
                           "size"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "enterTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sftime_id,
                           "exitTime"),
            node_interface(node_interface::eventout_id,
                           field_value::sfbool_id,
                           "isActive")
        };

        typedef node_type_impl<visibility_sensor_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & visibilitySensorNodeType =
            static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::center_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::center_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::center_)));
            } else if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfbool> >(
                            &visibility_sensor_node::enabled_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfbool> >(
                            &visibility_sensor_node::enabled_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfbool> >(
                            &visibility_sensor_node::enabled_)));
            } else if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_exposedfield(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_listener_ptr_ptr(
                        new node_type_t::event_listener_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::size_)),
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::size_)),
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::
                        exposedfield<sfvec3f> >(
                            &visibility_sensor_node::size_)));
            } else if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::sftime_emitter>(
                            &visibility_sensor_node::enter_time_emitter_)));
            } else if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::sftime_emitter>(
                            &visibility_sensor_node::exit_time_emitter_)));
            } else if (*interface == *++supported_interface) {
                visibilitySensorNodeType.add_eventout(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::event_emitter_ptr_ptr(
                        new node_type_t::event_emitter_ptr<
                        abstract_node<visibility_sensor_node>::sfbool_emitter>(
                            &visibility_sensor_node::is_active_emitter_)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class visibility_sensor_node
     *
     * @brief VisibilitySensor node instances.
     */

    /**
     * @var visibility_sensor_node::visibility_sensor_class
     *
     * @brief Class object for VisibilitySensor instances.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<visibility_sensor_node>::exposedfield<openvrml::sfvec3f> visibility_sensor_node::center_
     *
     * @brief center exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<visibility_sensor_node>::exposedfield<openvrml::sfbool> visibility_sensor_node::enabled_
     *
     * @brief enabled exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<visibility_sensor_node>::exposedfield<openvrml::sfvec3f> visibility_sensor_node::size_
     *
     * @brief size exposedField.
     */

    /**
     * @var openvrml::sfbool visibility_sensor_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter visibility_sensor_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @var openvrml::sftime visibility_sensor_node::enter_time_
     *
     * @brief enterTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter visibility_sensor_node::enter_time_emitter_
     *
     * @brief enterTime eventOut emitter.
     */

    /**
     * @var openvrml::sftime visibility_sensor_node::exit_time_
     *
     * @brief exitTime eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter visibility_sensor_node::exit_time_emitter_
     *
     * @brief exitTime eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    visibility_sensor_node::
    visibility_sensor_node(const node_type & type,
                           const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<visibility_sensor_node>(type, scope),
        child_node(type, scope),
        center_(*this, vec3f(0.0, 0.0, 0.0)),
        enabled_(*this, true),
        size_(*this, vec3f(0.0, 0.0, 0.0)),
        is_active_(false),
        is_active_emitter_(*this, this->is_active_),
        enter_time_(0.0),
        enter_time_emitter_(*this, this->enter_time_),
        exit_time_(0.0),
        exit_time_emitter_(*this, this->exit_time_)
    {
        this->node::modified(true);
    }

    /**
     * @brief Destroy.
     */
    visibility_sensor_node::~visibility_sensor_node() throw ()
    {}

    /**
     * @brief Generate visibility events.
     *
     * @todo This is in a render() method since the it needs to be computed
     *       with respect to the accumulated transformations above it in the
     *       scene graph. Move to update() when xforms are accumulated in
     *       Groups...
     *
     * @param viewer    viewer.
     * @param context   rendering_context.
     */
    void
    visibility_sensor_node::do_render_child(openvrml::viewer & viewer,
                                            rendering_context)
    {
        if (this->enabled_.sfbool::value()) {
            sftime timeNow(browser::current_time());
            vec3f xyz[2] = { this->center_.sfvec3f::value(),
                             this->center_.sfvec3f::value()
                             + this->size_.sfvec3f::value() };

            // hack: enclose box in a sphere...
            viewer.transform_points(2, &xyz[0]);
            float r  = (xyz[1] - xyz[0]).length();

            // Was the sphere visible last time through? How does this work
            // for USE'd nodes? I need a way for each USE to store whether
            // it was active.
            bool wasIn = this->is_active_.value();

            // Is the sphere visible? ...
            bool inside = xyz[0].z() < 0.0; // && z > - scene->visLimit()
            if (inside) {
                using openvrml_::fequal;

                openvrml::navigation_info_node & nav_info =
                    this->type().node_class().browser()
                    .active_navigation_info();
                if (!fequal<float>()(nav_info.visibility_limit(), 0.0f)
                    && xyz[0][2] < -(nav_info.visibility_limit())) {
                    inside = false;
                }
            }

            // This bit assumes 90degree fieldOfView to get rid of trig
            // calls...
            if (inside) {
                inside = fabs(xyz[0].x()) < -0.5 * xyz[0].z() + r
                    && fabs(xyz[0].y()) < -0.5 * xyz[0].z() + r;
            }

            // Just became visible
            if (inside && !wasIn) {
                this->is_active_.value(true);
                node::emit_event(this->is_active_emitter_, timeNow.value());

                this->enter_time_ = timeNow;
                node::emit_event(this->enter_time_emitter_, timeNow.value());
            }

            // Check if viewer has left the box
            else if (wasIn && !inside) {
                this->is_active_.value(false);
                node::emit_event(this->is_active_emitter_, timeNow.value());

                this->exit_time_ = timeNow;
                node::emit_event(this->exit_time_emitter_, timeNow.value());
            }
        } else {
            this->node::modified(false);
        }
    }


    /**
     * @brief Construct.
     *
     * @param browser the browser associated with this node_class.
     */
    world_info_class::world_info_class(openvrml::browser & browser):
        node_class(browser)
    {}

    /**
     * @brief Destroy.
     */
    world_info_class::~world_info_class() throw ()
    {}

    /**
     * @brief Create a node_type.
     *
     * @param id            the name for the new node_type.
     * @param interfaces    the interfaces for the new node_type.
     *
     * @return a boost::shared_ptr<node_type> to a node_type capable of
     *         creating WorldInfo nodes.
     *
     * @exception unsupported_interface if @p interfaces includes an interface
     *                                  not supported by world_info_class.
     * @exception std::bad_alloc        if memory allocation fails.
     */
    const boost::shared_ptr<openvrml::node_type>
    world_info_class::
    do_create_type(const std::string & id,
                   const node_interface_set & interfaces) const
        throw (unsupported_interface, std::bad_alloc)
    {
        typedef boost::array<node_interface, 2> supported_interfaces_t;
        static const supported_interfaces_t supported_interfaces = {
            node_interface(node_interface::field_id,
                           field_value::mfstring_id,
                           "info"),
            node_interface(node_interface::field_id,
                           field_value::sfstring_id,
                           "title")
        };

        typedef node_type_impl<world_info_node> node_type_t;

        const boost::shared_ptr<node_type> type(new node_type_t(*this, id));
        node_type_t & worldInfoNodeType = static_cast<node_type_t &>(*type);
        for (node_interface_set::const_iterator interface(interfaces.begin());
             interface != interfaces.end();
             ++interface) {
            supported_interfaces_t::const_iterator supported_interface =
                supported_interfaces.begin() - 1;
            if (*interface == *++supported_interface) {
                worldInfoNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<mfstring>(
                            &world_info_node::info)));
            } else if (*interface == *++supported_interface) {
                worldInfoNodeType.add_field(
                    supported_interface->field_type,
                    supported_interface->id,
                    node_type_t::field_ptr_ptr(
                        new node_type_t::field_ptr<sfstring>(
                            &world_info_node::title)));
            } else {
                throw unsupported_interface(*interface);
            }
        }
        return type;
    }

    /**
     * @class world_info_node
     *
     * @brief WorldInfo node instances.
     */

    /**
     * @var world_info_node::world_info_class
     *
     * @brief Class object for WorldInfo instances.
     */

    /**
     * @var openvrml::mfstring world_info_node::info
     *
     * @brief info field.
     */

    /**
     * @var openvrml::sfstring world_info_node::title
     *
     * @brief title field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the instance.
     * @param scope the scope that the new node will belong to.
     */
    world_info_node::
    world_info_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        abstract_node<world_info_node>(type, scope),
        child_node(type, scope)
    {}

    /**
     * @brief Destroy.
     */
    world_info_node::~world_info_node() throw ()
    {}
}
