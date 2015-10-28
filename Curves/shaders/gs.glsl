#version 330 core
layout (lines_adjacency) in; 
layout (line_strip, max_vertices = 6) out;
//layout (points, max_vertices = 2) out;

#define MAGNITUDE 0.1f
#define M_PI 3.14159265358979323846

out vec3 fVertexColor;

uniform mat4 mvp;

//http://math.etsu.edu/multicalc/prealpha/Chap1/Chap1-8/part4.htm

void main()
{

	vec4 point0 = gl_in[0].gl_Position;
	vec4 point1 = gl_in[1].gl_Position;
	vec4 point2 = gl_in[2].gl_Position;

	vec3 forward_tangent_vector =  vec3(normalize(point2 - point1)) ;
	vec3 backward_tangent_vector = vec3(normalize(point1 - point0)) ;

	vec3 second_order_tangent = normalize(forward_tangent_vector - backward_tangent_vector);

	vec3 binormal = normalize(cross(forward_tangent_vector, second_order_tangent));

	vec3 normal = normalize(cross(binormal, forward_tangent_vector));
	
	//Drawing Axes

	//fVertexColor = vec3(0, 1, 0);
	////tangent
	//gl_Position = mvp*point1; 
	//EmitVertex(); 
	//gl_Position = mvp*(point1 + MAGNITUDE*vec4(forward_tangent_vector,0)); 
	//EmitVertex();
	//EndPrimitive();
	//
	//fVertexColor = vec3(1, 0, 0);
	////binormal
	//gl_Position = mvp*point1; 
	//EmitVertex();	
	//gl_Position = mvp*(point1 + MAGNITUDE*vec4(binormal,0)); 
	//EmitVertex();
	//EndPrimitive();
	//
	//fVertexColor = vec3(0, 0, 1);
	////normal
	//gl_Position = mvp*point1; 
	//EmitVertex();	
	//gl_Position = mvp*(point1 + MAGNITUDE*vec4(normal,0)); 
	//EmitVertex();
	//EndPrimitive();

	mat3 tbn = mat3(forward_tangent_vector, binormal, normal);
	
	


	//Drawing Circles
	float dt = 2*M_PI / 100;
	for(int i = 0 ; i < 100; i++)
	{
		float x = cosf(dt * i);
		float y = sinf(dt * i);
		float z = 0;
	}

	
}