#include "space_object.h"


void Space_Object::update()
{
  //std::cout<<name_<<"\n";
  mat4 scaling = mat4(0);
  scaling = scaling.scale(radius_);

  mat4 translation = mat4(0);
  translation = translation.translate(vec3(distance_, 0,0));

  mat4 self_rotation = mat4(0);
  self_rotation = self_rotation.rotate_y(angle_self_);

  mat4 sun_rotation = mat4(0);
  sun_rotation = sun_rotation.rotate_y(angle_parent_);

  //mat4 tilt_rotation = mat4(0);
  //tilt_rotation = tilt_rotation.rotate_z(angle_tilt_);


  model_matrix_ = sun_rotation*translation*self_rotation*scaling;

  position_ = sun_rotation*(vec4(distance_, 0,0,1));





    /** \todo Update `model_matrix_` and position (`position_`) for each object.
    * 1. Combine translation and scaling matrices to get a result like in screenshots/planet_system_initial.png assuming:
    *   - sun at origin
    *   - all objects scaled by radius
    *   - all objects translated by `distance` in x direction
    * 2. Now use y-axis-rotation matrices in the right places to allow rotation
    *    around the object's axis (angle_self) and sun (angle_parent)
    * 3. You can also support a tilt angle if you like (`angle_tilt`) rotations
    * 4. Update the object's position using your constructed model matrix
    * Hints:
    *   - See glmath.h/cpp for an overview about implemented matrices.
    *   - Order is important!
    */

}

//-----------------------------------------------------------------------------

void Moon::update()
{


  mat4 scaling = mat4(0);
  scaling = scaling.scale(radius_);

  mat4 translation_distance = mat4(0);
  translation_distance = translation_distance.translate(vec3(distance_, 0,0));

  mat4 self_rotation = mat4(0);
  self_rotation = self_rotation.rotate_y(angle_self_);

  mat4 earth_rotation = mat4(0);
  earth_rotation = earth_rotation.rotate_y(angle_parent_);

  //mat4 tilt_rotation = mat4(0);
  //tilt_rotation = tilt_rotation.rotate_z(angle_tilt_);


  mat4 translate_to_pp = mat4(0);
  translate_to_pp = translate_to_pp.translate(parent_planet_->position_);



  model_matrix_ =
      translation_distance *earth_rotation*translate_to_pp*self_rotation*scaling;

  position_ = earth_rotation*self_rotation*(vec4(distance_, 0,0,1));

    /** \todo Update moon's `model_matrix_` and position (`position_`).
    *  The moon is a bit special, it must rotate around its `parent_planet_`. Be careful with the
    *  translation_distance-rotation-order since rotation matrices always rotate around the current origin.
    */

}
//-----------------------------------------------------------------------------

void Space_Object::create_glow(float outer_radius, vec3 color)
{
    // create Billboard
    glow_ = new Billboard;

    // initialize texture layout
    glow_->texture_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR,
                         GL_LINEAR, GL_REPEAT);

    // create texture image
    int res = 1024;
    glow_->create_glow_texture(res, (int)(res / (2.0 * outer_radius)) - 1,
                               res / 2 - 1, color);

    // initialize quad vertex layouts
    glow_->init_GL_arrays();
}

//-----------------------------------------------------------------------------

void Space_Object::update_glow_angles(vec3 eye)
{
    if (glow_ != nullptr)
    {
        vec3 pos_to_eye = normalize(vec3(eye) - vec3(position_));
        glow_->update_angles(pos_to_eye);
    }
}

//=============================================================================
