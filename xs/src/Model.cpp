#include "Model.hpp"

namespace Slic3r {

Model::~Model()
{
    for (t_model_materials::iterator it = this->materials.begin(); it != this->materials.end(); ++it)
        delete it->second;
    for (t_model_objects::iterator it = this->objects.begin(); it != this->objects.end(); ++it)
        delete *it;
}

ModelObject*
Model::add_object()
{
    ModelObject* retval = new ModelObject(this);
    this->objects.push_back(retval);
    return retval;
}

ModelObject*
Model::add_object(const ModelObject &object)
{
    ModelObject* retval = new ModelObject(this, object);
    this->objects.push_back(retval);
    return retval;
}

void
Model::delete_object(size_t obj_idx)
{
    this->objects.erase(this->objects.begin() + obj_idx);
}

void
Model::delete_all_objects()
{
    this->objects.clear();
}

ModelMaterial*
Model::set_material(t_model_material_id material_id, const t_model_material_attributes &attributes)
{
    ModelMaterial* material;
    
    // create material if it does not exist
    t_model_materials::iterator itm = this->materials.find(material_id);
    if (itm == this->materials.end()) {
        material = new ModelMaterial(this);
        this->materials[material_id] = material;
    } else {
        material = *itm;
    }
    
    // apply attributes
    for (t_model_material_attributes::const_iterator it = attributes.begin(); it != attributes.end(); ++it) {
        material->attributes[it->first] = it->second;
    }
    
    return material;
}

void
Model::duplicate_objects_grid(unsigned int x, unsigned int y, coordf_t distance)
{
    if (this->objects.size() > 1) throw "Grid duplication is not supported with multiple objects";
    
    ModelObject* object = this->objects.front();
    object->instances.clear();
    
    BoundingBoxf3 bb;
    object->bounding_box(&bb);
    Sizef3 size = bb.size();
    
    for (unsigned int x_copy = 1; x_copy <= x; ++x_copy) {
        for (unsigned int y_copy = 1; y_copy <= y; ++y_copy) {
            ModelInstance* instance = object->add_instance();
            instance->offset.x = (size.x + distance) * (x_copy-1);
            instance->offset.y = (size.y + distance) * (y_copy-1);
        }
    }
}

}
