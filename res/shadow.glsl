#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 u_rectangle;
uniform float u_roundness;
uniform float u_shadowRadius;
uniform float u_shadowSize;
uniform vec4 u_shadowColor;
uniform vec2 u_shadowOffset;

float RBSDF(vec2 centerPosition, vec2 size, float radius)
{
    if (min(size.x, size.y) < radius)
        radius = min(size.x, size.y);
    return length(max(abs(centerPosition) - size + radius, 0.)) - radius;
}

void main()
{
    vec2 size = u_rectangle.zw / 2.;
    vec2 position = gl_FragCoord.xy - u_rectangle.xy - size;
    float rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));
    float shadowRBSDF = 1. + rectangleRBSDF - smoothstep(0., u_shadowRadius, RBSDF(position - u_shadowOffset, size + u_shadowSize, u_roundness));
    gl_FragColor = u_shadowColor * shadowRBSDF;
}
