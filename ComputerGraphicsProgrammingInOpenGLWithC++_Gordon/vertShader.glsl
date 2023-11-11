#version 430
uniform float sideLength;
float convertFactor = 2 * sideLength / 600;
void main(void) {
	if (gl_VertexID==0) gl_Position = vec4(0.0,0.577*convertFactor,0.0,1.0);
	else if (gl_VertexID==1) gl_Position = vec4(0.5*convertFactor,-0.289*convertFactor,0.0,1.0);
	else if (gl_VertexID==2) gl_Position = vec4(-0.5*convertFactor,-0.289*convertFactor,0.0,1.0);
}