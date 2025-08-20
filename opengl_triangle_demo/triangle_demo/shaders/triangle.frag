#version 150 core
in vec3 vColor;
uniform float u_time;
out vec4 FragColor;
void main() {
    float pulse = abs(sin(u_time));
    FragColor = vec4(vColor * pulse, 1.0);
}
