#include "FileLoader.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace math;

Mesh FileLoader::load_OBJ(std::string path) {

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file at: " + path);
    }

    Mesh mesh = Mesh();

    std::vector<Vector3> temp_vertices, temp_normals;
    std::vector<Vector2> temp_textures;
    std::vector<int> vertex_indexes, texture_indexes, normal_indexes;

    while (file.peek() != EOF) {
        std::string line;
        getline(file, line);
        std::string header;
        while (file >> header) {
            if (header == "v") {
                /* Vertex coordinates <x> <y> <z>*/
                Vector3 vertex;
                file >> vertex.x >> vertex.y >> vertex.z;
                temp_vertices.push_back(vertex);
            }
            else if (header == "vt") {
                /* Vertex texture uv coordinates <u> <v> */
                Vector2 uvmap;
                file >> uvmap.x >> uvmap.y;
                temp_textures.push_back(uvmap);
            }
            else if (header == "vn") {
                /* Vertex normal vector <x> <y> <z> */
                Vector3 normal;
                file >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }
            else if (header == "f") {
                /*
                 * Face's vertices.
                 * These are indexes, not coordinates.
                 * Starts at 1.
                 * <v1>/<vt1>/<vn1> <v2>/<vt2>/<vn2> <v3>/<vt3>/<vn3>
                 * (Only triangles supported)
                 */

                int triangle_vertex_index[3], triangle_texture_index[3], triangle_normal_index[3];

                for (int i = 0; i < 3; i++) {
                    ((file >> triangle_vertex_index[i]).ignore()
                        >> triangle_texture_index[i]).ignore()
                        >> triangle_normal_index[i];
                    vertex_indexes.push_back(triangle_vertex_index[i]);
                    texture_indexes.push_back(triangle_texture_index[i]);
                    normal_indexes.push_back(triangle_normal_index[i]);
                }

            }
        }
    }

    /*
    * Get vertex coordinates from index.
    */

    for (unsigned int i = 0; i < vertex_indexes.size(); i++) {
        int vertex_index = vertex_indexes[i];
        int texture_index = texture_indexes[i];
        int normal_index = normal_indexes[i];
        Vector3 vertex = temp_vertices[vertex_index - 1];
        Vector2 texture = temp_textures[texture_index - 1];
        Vector3 normal = temp_normals[normal_index - 1];
        mesh.vertices.push_back(vertex);
        mesh.texture_map.push_back(texture);
        mesh.normals.push_back(normal);
    }

    return mesh;
}

Texture FileLoader::load_PNG(std::string path)
{
    
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(path.c_str());
    FIBITMAP* bitmap = FreeImage_Load(fif, path.c_str());
    if (bitmap == nullptr) {
        return { 0, nullptr, 0, 0 };
    }
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    unsigned int w = FreeImage_GetWidth(bitmap);
    unsigned int h = FreeImage_GetHeight(bitmap);
    BYTE* data = FreeImage_GetBits(bitmap);

    unsigned int id;

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
  
    return {id, data, w, h};
}
