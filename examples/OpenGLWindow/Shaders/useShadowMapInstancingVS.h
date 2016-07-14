//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* useShadowMapInstancingVertexShader= \
"#version 330 \n"
"precision highp float;\n"
"layout (location = 0) in vec4 position;\n"
"layout (location = 1) in vec4 instance_position;\n"
"layout (location = 2) in vec4 instance_quaternion;\n"
"layout (location = 3) in vec2 uvcoords;\n"
"layout (location = 4) in vec3 vertexnormal;\n"
"layout (location = 5) in vec4 instance_color;\n"
"layout (location = 6) in vec3 instance_scale;\n"
"uniform mat4 ModelViewMatrix;\n"
"uniform mat4 ProjectionMatrix;\n"
"uniform mat4 DepthBiasModelViewProjectionMatrix;\n"
"uniform mat4 MVP;\n"
"uniform vec3 lightDirIn;\n"
"out vec4 ShadowCoord;\n"
"out Fragment\n"
"{\n"
"     vec4 color;\n"
"} fragment;\n"
"out Vert\n"
"{\n"
"	vec2 texcoord;\n"
"} vert;\n"
"vec4 quatMul ( in vec4 q1, in vec4 q2 )\n"
"{\n"
"    vec3  im = q1.w * q2.xyz + q1.xyz * q2.w + cross ( q1.xyz, q2.xyz );\n"
"    vec4  dt = q1 * q2;\n"
"    float re = dot ( dt, vec4 ( -1.0, -1.0, -1.0, 1.0 ) );\n"
"    return vec4 ( im, re );\n"
"}\n"
"vec4 quatFromAxisAngle(vec4 axis, in float angle)\n"
"{\n"
"    float cah = cos(angle*0.5);\n"
"    float sah = sin(angle*0.5);\n"
"	float d = inversesqrt(dot(axis,axis));\n"
"	vec4 q = vec4(axis.x*sah*d,axis.y*sah*d,axis.z*sah*d,cah);\n"
"	return q;\n"
"}\n"
"//\n"
"// vector rotation via quaternion\n"
"//\n"
"vec4 quatRotate3 ( in vec3 p, in vec4 q )\n"
"{\n"
"    vec4 temp = quatMul ( q, vec4 ( p, 0.0 ) );\n"
"    return quatMul ( temp, vec4 ( -q.x, -q.y, -q.z, q.w ) );\n"
"}\n"
"vec4 quatRotate ( in vec4 p, in vec4 q )\n"
"{\n"
"    vec4 temp = quatMul ( q, p );\n"
"    return quatMul ( temp, vec4 ( -q.x, -q.y, -q.z, q.w ) );\n"
"}\n"
"out vec3 lightDir,normal,ambient;\n"
"void main(void)\n"
"{\n"
"	vec4 q = instance_quaternion;\n"
"	ambient = vec3(0.5,.5,0.5);\n"
"			\n"
"	vec4 worldNormal = (quatRotate3( vertexnormal,q));\n"
"	\n"
"	normal = normalize(worldNormal).xyz;\n"
"	lightDir = lightDirIn;\n"
"		\n"
"	\n"
"	vec4 localcoord = quatRotate3( position.xyz*instance_scale,q);\n"
"	vec4 vertexPos = MVP* vec4((instance_position+localcoord).xyz,1);\n"
"	gl_Position = vertexPos;\n"
"	ShadowCoord = DepthBiasModelViewProjectionMatrix * vec4((instance_position+localcoord).xyz,1);\n"
"	fragment.color = instance_color;\n"
"	vert.texcoord = uvcoords;\n"
"}\n"
;
