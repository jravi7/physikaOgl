#version 330 core
layout (lines_adjacency) in; 
layout (line_strip, max_vertices = 6) out;
//layout (points, max_vertices = 1) out;

out vec3 fVertexColor;
void main()
{
	
	vec3 forward_tangent_vector = vec3(normalize(gl_in[2].gl_Position - gl_in[1].gl_Position)) ;
	vec3 backward_tangent_vector = vec3(normalize(gl_in[1].gl_Position - gl_in[0].gl_Position)) ;

	vec3 second_order_tangent = normalize(forward_tangent_vector - backward_tangent_vector);

	vec3 binormal = normalize(cross(forward_tangent_vector, second_order_tangent));

	vec3 normal = normalize(cross(binormal, forward_tangent_vector));
	
	fVertexColor = vec3(0, 1, 0);
	//tangent
	gl_Position = gl_in[1].gl_Position; 
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + 5.f * vec4(forward_tangent_vector,1); 
	EmitVertex();
	EndPrimitive();

	fVertexColor = vec3(1, 0, 0);
	//binormal
	gl_Position = gl_in[1].gl_Position; 
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + 5.f * vec4(binormal,1); 
	EmitVertex();
	EndPrimitive();

	fVertexColor = vec3(0, 0, 1);
	//normal
	gl_Position = gl_in[1].gl_Position; 
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + 5.f * vec4(normal,1); 
	EmitVertex();
	EndPrimitive();


	
}