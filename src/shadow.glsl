#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture0;
uniform vec2 u_resolution;

uniform vec4 u_rectangle;
uniform float u_roundness;
uniform float u_shadowRadius;
uniform float u_shadowSize;
uniform vec4 u_shadowColor;
uniform vec2 u_shadowOffset;

// https://iquilezles.org/articles/distfunctions
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
    vec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);
    gl_FragColor = bgcolor + vec4(u_shadowColor * shadowRBSDF);
}
