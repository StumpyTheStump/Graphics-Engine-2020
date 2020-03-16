#version 450

uniform vec4 color = vec4(1,1,1,1);

uniform vec4 base_colour;
uniform vec3 light_direction;
uniform vec3 light_color;
uniform float specular_power;
uniform vec3 camera_position;
out vec4 final_color;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

in vec4 cheap_colour;
in vec3 vNormal;
in vec4 vPosition;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vTexCoord;

void main()
{
	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(light_direction);
	
	
	vec3 texNormal = texture(normalTexture, vTexCoord).xyz;
	mat3 TBN = mat3(T,B,N);
	N = TBN * (texNormal * 2 - 1);
	//N = texNormal.xyz;// * 2 - 1);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) ); 

	vec3 V = normalize(camera_position - vPosition.xyz);
	vec3 R = reflect( L, N );
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specular_power );

	
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).xyz;
	
	vec4 ambiance = base_colour;
	vec4 diffuse = vec4 (texDiffuse * light_color * lambertTerm, 1);
	vec4 specular = vec4 (light_color * specularTerm, 1);
    
	final_color = vec4 (ambiance.xyz + diffuse.xyz + specular.xyz, 1);// * 0.001 + vec4(N,1); 
	//final_color = cheap_colour;
}