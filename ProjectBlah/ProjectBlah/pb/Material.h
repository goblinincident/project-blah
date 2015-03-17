#pragma once


namespace pb
{
	class Renderable;
	class VertexObjectData;


	class Material
	{

		friend class Renderable;

		/** @brief Generates a vertex buffer object for 
		* this material.
		* (called by Renderable)
		**/
		unsigned int CreateVBO(VertexObjectData* vo_data);

	public:

		enum AttributeFlags
		{
			NONE = 0,
			POSITION = 1 << 0
		};

		enum UniformFlags
		{
			NONE = 0,
			MVP = 1 << 0
		};

		static Material default_material;

		Material(/*shader options etc*/);

		void SetShader(
			const char* vertex_shader_path = nullptr,
			const char* fragment_shader_path = nullptr,
			unsigned int attribute_flags = AttributeFlags::POSITION,
			unsigned int uniform_flags = UniformFlags::MVP);


	private:

		unsigned int attribute_flags_;
		unsigned int uniform_flags_;

		const char*		vertex_shader_path_;
		const char*		vertex_shader_code_;

		const char*		fragment_shader_path_;
		const char*		fragment_shader_code_;

		unsigned int shader_program_id_;


		unsigned int* index_data_;
		unsigned int vao_;


		unsigned int load_shader(const char* shader_source, unsigned int type);
		const char* read_shader(const char* shader_path);
		void check_shader_program(unsigned int program_id);
	};


};