#ifndef slic3r_Model_hpp_
#define slic3r_Model_hpp_

#include <myinit.h>
#include "Config.hpp"
#include "Layer.hpp"
#include "Point.hpp"
#include "TriangleMesh.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace Slic3r {

class ModelInstance;
class ModelMaterial;
class ModelObject;
class ModelVolume;

typedef std::string t_model_material_id;
typedef std::string t_model_material_attribute;
typedef std::map<t_model_material_attribute,std::string> t_model_material_attributes;

class Model
{
    typedef std::map<t_model_material_id,ModelMaterial*> t_model_materials;
    typedef std::vector<ModelObject*> t_model_objects;
    
    public:
    t_model_materials materials;
    t_model_objects objects;
    
    Model() {};
    ~Model();
    ModelObject* add_object();
    ModelObject* add_object(const ModelObject &object);
    void delete_object(size_t obj_idx);
    void delete_all_objects();
    ModelMaterial* set_material(t_model_material_id material_id, const t_model_material_attributes &attributes);
    void duplicate_objects_grid(unsigned int x, unsigned int y, coordf_t distance);
    void duplicate_objects(size_t copies_num, coordf_t distance, const BoundingBoxf &bb);
    void arrange_objects(coordf_t distance, const BoundingBoxf &bb);
    void duplicate(size_t copies_num, coordf_t distance, const BoundingBoxf &bb);
    bool has_objects_with_no_instances() const;
    void bounding_box(BoundingBoxf3* bb) const;
    void align_to_origin();
    void center_instances_around_point(const Pointf &point);
    void translate(coordf_t x, coordf_t y, coordf_t z);
    void mesh(TriangleMesh* mesh) const;
    void split_meshes();
    std::string get_material_name(t_model_material_id material_id);
    
    private:
    void _arrange(const std::vector<Size> &sizes, coordf_t distance, const BoundingBoxf &bb, Pointfs* positions) const;
};

class ModelMaterial
{
    public:
    ModelMaterial(Model* _model) : model(_model) {};
    t_model_material_attributes attributes;
    DynamicConfig config;
    Model* getModel() const;
    
    private:
    Model* model;
};

class ModelObject
{
    public:
    std::string input_file;
    std::vector<ModelInstance*> instances;
    std::vector<ModelVolume*> volumes;
    DynamicConfig config;
    t_layer_height_ranges layer_height_ranges;
    Vector origin_translation;  // translation vector applied by center_around_origin() 
    
    ModelObject(Model* _model) : model(_model) {};
    ModelObject(Model* _model, const ModelObject &object);
    ~ModelObject();
    ModelInstance* add_instance();
    ModelInstance* add_instance(const ModelInstance &instance);
    ModelVolume* add_volume();
    ModelVolume* add_volume(const ModelVolume &volume);
    void delete_volume(size_t volume_idx);
    void delete_last_instance();
    void raw_mesh(TriangleMesh* mesh) const;
    void mesh(TriangleMesh* mesh) const;
    void bounding_box(BoundingBoxf3* bb);
    void instance_bounding_box(size_t instance_idx, BoundingBoxf3* bb) const;
    void center_around_origin();
    void translate(coordf_t x, coordf_t y, coordf_t z);
    size_t materials_count() const;
    void unique_materials(std::vector<t_model_material_id>* materials) const;
    size_t facets_count() const;
    bool needed_repair() const;
    
    private:
    Model* model;
    BoundingBoxf bb;
    void update_bounding_box();
};

class ModelVolume
{
    public:
    ModelVolume(ModelObject* _object) : object(_object), modifier(false) {};
    t_model_material_id material_id;
    TriangleMesh mesh;
    bool modifier;
    
    ModelMaterial* assign_unique_material();
    
    private:
    ModelObject* object;
};

class ModelInstance
{
    public:
    double rotation;
    double scaling_factor;
    Pointf offset;
    
    ModelInstance(ModelObject* _object) : object(_object), rotation(0), scaling_factor(1) {};
    void transform_mesh(TriangleMesh* mesh, bool dont_translate) const;
    void transform_polygon(Polygon* polygon) const;
    
    private:
    ModelObject* object;
};

}

#endif
