/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/15 12:14:39 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
#define TEXTURE_H

# include <stdint.h>


/*
 * bf_type: file type (must be 0x4d42 (assci string "BM"))
 * bs_size: bitmap file size
 * bs_reserve1: reserved (must be 0) 
 * bs_reserve2: reserved (must be 0) 
 * bs_off_bits: offset in bytes from the begining of bitmap_file_header struct to the bitmap bits
 *
 * https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
*/
typedef struct bitmap_file_header
{
	uint16_t	bf_type;
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_off_bits;

}	t_bitmap_file_header;


/*
 * bi_size: nb bytes require for struct
 * bi_width: width of bitmap in pixel
 * bi_height: height of bitmap in pixel, if >0 then bitmap is botom-up and origin is lower left cornerif <0 then bitmap is top-down and origin is upper-left corner
 * bi_planes: nb plane for device (value must be set to 1)
 * bi_bit_count: nb bit per pixel (must be 0, 1, 4, 8, 16, 24, 32)
 * bi_compression: compression type for a bottom-up bitmap (must be BI_RGB, BI_RLE8, BI_RLE4, BI_BITFIELDS, BI_JPEG, BI_PNG)
 * bi_clr_used: nb of color indexes in color table
 * bi_clr_important: nb color indexed requiered, if 0 then all colors are required
 *
 * https://learn.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
*/
typedef struct bitmap_info_header
{
	uint32_t	bi_size;
	int32_t		bi_width;
	int32_t		bi_height;
	uint16_t	bi_planes;
	uint16_t	bi_bit_count;
	uint32_t	bi_compression;
	uint32_t	bi_size_image;
	int32_t		bi_xpels_per_meter;
	int32_t		bi_ypels_per_meter;
	uint32_t	bi_clr_used;
	uint32_t	bi_clr_important;
}	t_bitmap_info_header;	

#endif // !TEXTURE_H
