/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//! \file
//! \brief Header provides template of SPI and spi drivers configuration.
#ifndef PLATFORM_SPI_CFGS_HPP_
#define PLATFORM_SPI_CFGS_HPP_

#include <aux/platform_defines.hpp>
#include <aux/spi.hpp>

namespace ecl
{

//! \addtogroup platform Platform defintions and drivers
//! @{

//! \addtogroup skel Platform skeleton
//! @{

//! \defgroup skel_templates Auto-generated code, Python COG and CMake templates
//! for platform skeleton.
//! @{

/*[[[cog
import cog
import json

cfg = json.load(open(JSON_CFG))
cfg = cfg['platform']

]]]*/
//[[[end]]]

// SPI configuration -----------------------------------------------------------

/*[[[cog

# Maps SPI config values to correct definitions
spi_mapping = {
    'type' : {
        'master'        : 'ecl::spi_type::master',
        # TODO: slave mode is not implemented
        # 'slave'       : 'ecl::spi_type::slave'
    },
    'cpol': {
        'high'          : 'ecl::spi_cpol::high',
        'low'           : 'ecl::spi_cpol::low'
    },
    'cpha': {
        'high'          : 'ecl::spi_cpha::high',
        'low'           : 'ecl::spi_cpha::low'
    },
}

# Template for SPI config
spi_cfg_struct = '''
template<>
struct spi_cfg<spi_channel::ch%(spi_ch)d>
{
    static constexpr auto type = %(spi_type)s;
    static constexpr auto cpol = %(spi_cpol)s;
    static constexpr auto cpha = %(spi_cpha)s;
};

'''

# Template for driver typedef
spi_typedef = 'using %s = spi<spi_device::bus%d>;'
# Alias template (optional)
spi_alias = 'using %s = %s;'

spi_cfgs = {}
if 'spi' in cfg:
    spi_cfgs = cfg['spi']

for spi in spi_cfgs:
    id = int(spi['id'][-1])
    spi_name = 'spi_' + str(id) + '_driver'

    # Directly included values
    values = {
        'spi_ch' : id,
    }

    # Values that require mapping
    for k, v in spi_mapping.items():
        json_value = spi[k]
        values[k] = v[json_value]

    if 'comment' in spi:
        cog.outl('/' + '* ' + spi['comment'] + ' *' + '/')

    cog.outl(spi_cfg_struct % values)
    cog.outl(spi_typedef % (spi_name, id))

    if 'alias' in spi:
        cog.outl(spi_alias % (spi['alias'], spi_name))

]]]*/
//[[[end]]]

//! @}

//! @}

//! @}

} // namespace ecl

#endif // PLATFORM_SPI_CFGS_HPP_
