#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture0;
uniform vec2 u_resolution;

// Custom uniforms
uniform float u_blurRadius;
// Quality is fixed inside the shader so a reload is required to change the quality.
const float c_blurQuality = 2.5;

void main()
{
    // The magic number here is Tau / 4 (or Pi / 2)
    float blurRadius = u_blurRadius / c_blurQuality * 1.570796327;
    vec4 finalColor = vec4(0.);
    for (float a = -c_blurQuality; a <= c_blurQuality; a++)
        for (float b = -c_blurQuality; b <= c_blurQuality; b++)
            finalColor += texture2D(texture0, (gl_FragCoord.xy + vec2(a * blurRadius, b * blurRadius)) / u_resolution);
    finalColor /= 4. * c_blurQuality * c_blurQuality + 4. * c_blurQuality + 1.;

    gl_FragColor = finalColor;
}
