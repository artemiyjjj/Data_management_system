#include <stdint.h>

typedef uint32_t block_index; 
typedef uint32_t block_offset;



/* Signatures that defines types of blocks.
    - Type block contains available data types for the application.
    - Data block contains cells, which are responsible for storing application data of particular type.
    - Head block contains positions of the data-blocks, which are containing start of a new document tree.
*/
enum block_signature {
    Bl_sign_Head = 0,
    Bl_sign_Data,
    Bl_sign_Types,
};