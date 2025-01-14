#include "blendmode.hpp"

using namespace SDL;

BlendMode ComposeCustomBlendMode(
    BlendFactor srcColourFactor,
    BlendFactor dstColourFactor,
    BlendOperation colourOperation,
    BlendFactor srcAlphaFactor,
    BlendFactor dstAlphaFactor,
    BlendOperation alphaOperation
) {
    return BlendMode(SDL_ComposeCustomBlendMode(
        SDL_BlendFactor(srcColourFactor),
        SDL_BlendFactor(dstColourFactor),
        SDL_BlendOperation(colourOperation),
        SDL_BlendFactor(srcAlphaFactor),
        SDL_BlendFactor(dstAlphaFactor),
        SDL_BlendOperation(alphaOperation)
    ));
}
