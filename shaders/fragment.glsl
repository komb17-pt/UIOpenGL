#version 330 core
out vec4 FragColor;

in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // Calculate an approximate normal using derivatives.
    vec3 normal = normalize(cross(dFdx(FragPos), dFdy(FragPos)));

    // Use a constant light direction.
    vec3 lightDir = normalize(vec3(1.0));

    // Diffuse lighting calculation.
    float diff = max(dot(normal, lightDir), 0.0);

    // Combine ambient and diffuse terms. Ambient is a fixed low value.
    vec3 color = (0.2 + diff) * objectColor * lightColor;

    FragColor = vec4(color, 1.0);
}
