/**
 * Copyright (C) 2010 - 2010, Vrai Stacey.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef INC_FUDGE_CPP_CODEC_HPP
#define INC_FUDGE_CPP_CODEC_HPP

#include "fudge-cpp/envelope.hpp"

namespace fudge {

class codec
{
    public:
        envelope decode ( const fudge_byte * bytes, fudge_i32 numbytes ) const;

        void encode ( const envelope & source, fudge_byte * & bytes, fudge_i32 & numbytes ) const;
};

}

#endif

