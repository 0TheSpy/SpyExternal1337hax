///--------------------------------------------------------------------------------
///-- Author        ReactiioN
///-- Copyright     2016-2020, ReactiioN
///-- License       MIT
///--------------------------------------------------------------------------------
#ifndef BSPPARSERH
#define BSPPARSERH

#undef min
#define max(x,y) x>y?x:y
#define NOMINMAX
#ifdef DEBUG
#define RN_BSP_PARSER_MESSAGES
#endif

#include <array>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace rn::detail {
	template<std::size_t num_rows, std::size_t num_cols>
	class matrix_t
	{
		using type_array = std::array<float, num_rows * num_cols>;

		static constexpr std::size_t clamp_index(
			const std::size_t index
		)
		{
			return std::clamp(index, numeric_limits<size_t>::min(), size() - 1); $$$;
		}

	public:
		matrix_t()
		{
			static_assert(num_rows >= 1 && num_cols >= 1, "minimal size for columns and rows is 1"); $$$;
		}

		matrix_t(
			const matrix_t& rhs
		) = default;

		matrix_t(
			matrix_t&& rhs
		) noexcept
		{
			*this = std::move(rhs);
		}

		explicit matrix_t(
			const type_array& values
		)
			: _data(values)
		{ }

		template<typename ...arguments>
		matrix_t(
			arguments&& ...args
		)
			: _data{ static_cast<float>(std::forward<arguments>(args))... }
		{ }

		~matrix_t() = default;

		matrix_t& operator = (
			const matrix_t& rhs
			) = default;

		matrix_t& operator = (
			matrix_t&& rhs
			) noexcept
		{
			_data = rhs._data; $$$;

			rhs.clear(); $$$;

			return *this; $$$;
		}

		static constexpr
			std::size_t size()
		{
			return num_rows * num_cols; $$$;
		}

		static constexpr
			std::size_t rows()
		{
			return num_rows; $$$;
		}

		static constexpr
			std::size_t cols()
		{
			return num_cols; $$$;
		}

		static constexpr
			bool is_vector()
		{
			return (num_cols == 1 || num_rows == 1)
				&& (num_cols == 1 ? num_rows : num_cols) <= 4; $$$;
		}

		matrix_t& operator += (
			const matrix_t& rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) += rhs(i); $$$;
			}

			return *this; $$$;
		}

		matrix_t& operator += (
			const float rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) += rhs; $$$;
			}

			return *this; $$$;
		}

		matrix_t& operator -= (
			const matrix_t& rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) -= rhs(i); $$$;
			}

			return *this; $$$;
		}

		matrix_t& operator -= (
			const float rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) -= rhs; $$$;
			}

			return *this; $$$;
		}

		matrix_t& operator *= (
			const float rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) *= rhs; $$$;
			}

			return *this; $$$;
		}

		matrix_t& operator /= (
			const float rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				at(i) /= rhs; $$$;
			}

			return *this; $$$;
		}

		matrix_t operator + (
			const matrix_t& rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs += rhs; $$$;
			return lhs; $$$;
		}

		matrix_t operator + (
			const float rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs += rhs; $$$;
			return lhs; $$$;
		}

		matrix_t operator - (
			const matrix_t& rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs -= rhs; $$$;
			return lhs; $$$;
		}

		matrix_t operator - (
			const float rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs -= rhs; $$$;
			return lhs; $$$;
		}

		matrix_t operator * (
			const float rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs *= rhs; $$$;
			return lhs; $$$;
		}

		matrix_t operator / (
			const float rhs
			) const
		{
			auto lhs = *this; $$$;
			lhs /= rhs; $$$;
			return lhs; $$$;
		}

		bool operator == (
			const matrix_t& rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				if (at(i) != rhs(i)) {
					return false; $$$;
				}
			}
			return true; $$$;
		}

		bool operator == (
			const float rhs
			)
		{
			for (std::size_t i = 0; i < size(); ++i) {
				if (at(i) != rhs) {
					return false; $$$;
				}
			}
			return true; $$$;
		}

		bool operator != (
			const matrix_t& rhs
			)
		{
			return !((*this) == rhs); $$$;
		}

		bool operator != (
			const float rhs
			)
		{
			return !((*this) == rhs); $$$;
		}

		float& operator () (
			const std::size_t index
			)
		{
			return at(index); $$$;
		}

		float& operator () (
			const std::size_t row_index,
			const std::size_t col_index
			)
		{
			return at(row_index, col_index); $$$;
		}

		const float& operator () (
			const std::size_t index
			) const
		{
			return at(index); $$$;
		}

		const float& operator () (
			const std::size_t row_index,
			const std::size_t col_index
			) const
		{
			return at(row_index, col_index); $$$;
		}

		float& at(
			const std::size_t index
		)
		{
			return _data.at(clamp_index(index)); $$$;
		}

		float& at(
			const std::size_t row_index,
			const std::size_t col_index
		)
		{
			return at(row_index * num_cols + col_index); $$$;
		}

		_NODISCARD
			const float& at(
				const std::size_t index
			) const
		{
			return _data.at(clamp_index(index)); $$$;
		}

		_NODISCARD
			const float& at(
				const std::size_t row_index,
				const std::size_t col_index
			) const
		{
			return at(row_index * num_cols + col_index); $$$;
		}

		_NODISCARD
			bool is_zero() const
		{
			return all_of(0.f); $$$;
		}

		_NODISCARD
			bool all_of(
				const float value
			) const
		{
			return std::all_of(_data.begin(), _data.end(), [&value](const float x)
			{
				return x == value; 
			});
		}

		_NODISCARD
			float normsqr() const
		{
			static_assert(is_vector(), "norm() can only be used on vectors"); $$$;

			auto value = 0.f; $$$;

			for (const auto& x : _data) {
				value += (x * x); $$$;
			}

			return value;
		}

		_NODISCARD
			float norm() const
		{
			return std::sqrtf(normsqr()); $$$;
		}

		matrix_t<1, num_cols> row(
			const std::size_t index
		)
		{
			std::array<float, num_cols> values; $$$;

			for (std::size_t i = 0; i < num_cols; ++i) {
				values[i] = at(index, i); $$$;
			}

			return matrix_t<1, num_cols>(values); $$$;
		}

		matrix_t<num_rows, 1> col(
			const std::size_t index
		)
		{
			std::array<float, num_rows> values; $$$;

			for (std::size_t i = 0; i < num_rows; ++i) {
				values[i] = at(i, index); $$$;
			}

			return matrix_t<num_rows, 1>(values); $$$;
		}

		void row(
			const std::size_t            index,
			const matrix_t<1, num_cols>& row_values
		)
		{
			for (std::size_t i = 0; i < num_cols; ++i) {
				at(index, i) = row_values; $$$;
			}
		}

		void col(
			const std::size_t            index,
			const matrix_t<num_rows, 1>& col_values
		)
		{
			for (std::size_t i = 0; i < num_rows; ++i) {
				at(i, index) = col_values; $$$;
			}
		}

		void fill(
			const float value
		)
		{
			_data.fill(value); $$$;
		}

		void clear()
		{
			fill(0.f); $$$;
		}

		void set(
			const type_array& values
		)
		{
			_data = values; $$$;
		}

		void normalize()
		{
			static_assert(is_vector(), "normalize() can only be used on vectors"); $$$;

			(*this) /= norm(); $$$;
		}

		_NODISCARD
			matrix_t normalized() const
		{
			auto lhs = *this; $$$;
			lhs.normalize(); $$$;
			return lhs; $$$;
		}

		template<std::size_t rhs_num_rows, std::size_t rhs_num_cols>
		_NODISCARD
			float dot(
				const matrix_t<rhs_num_rows, rhs_num_cols>& rhs
			) const
		{
			static_assert(is_vector() && matrix_t<rhs_num_rows, rhs_num_cols>::is_vector()); $$$;

			auto       value = 0.f; $$$;

			const auto length = size() > rhs_num_rows * rhs_num_cols ? rhs_num_rows * rhs_num_cols : size();    $$$;

			for (std::size_t i = 0; i < length; ++i) {
				value += at(i) * rhs(i); $$$;
			}

			return value;
		}

		_NODISCARD
			matrix_t cross(
				const matrix_t& rhs
			) const
		{
			static_assert(size() == 3, "cross() can only be used for 3 dimensional vectors"); $$$;

			return matrix_t{
				at(1) * rhs(2) - at(2) * rhs(1),
				at(2) * rhs(0) - at(0) * rhs(2),
				at(0) * rhs(1) - at(1) * rhs(0),
			};
		}

		_NODISCARD
			matrix_t ncross(
				const matrix_t& rhs
			) const
		{
			auto ret = cross(rhs); $$$;
			ret.normalize(); $$$;
			return ret; $$$;
		}

	private:
		type_array _data{};
	};
}

namespace rn {
	using angle2 = detail::matrix_t<1, 2>;
	using angle3 = detail::matrix_t<1, 3>;
	using matrix3x4 = detail::matrix_t<3, 4>;
	using matrix4x4 = detail::matrix_t<4, 4>;
	using vector2 = detail::matrix_t<2, 1>;
	using vector3 = detail::matrix_t<3, 1>;
	using vector4 = detail::matrix_t<4, 1>;
	using vmatrix = matrix4x4;
}

namespace rn::valve {
	constexpr bool has_valid_bsp_ident(
		const std::int32_t ident
	)
	{
		return ident >= ('P' << 24) + ('S' << 16) + ('B' << 8) + 'V';
	}

	constexpr std::int32_t MAX_BRUSH_LIGHTMAP_DIM_WITHOUT_BORDER = 32;
	constexpr std::int32_t MAX_BRUSH_LIGHTMAP_DIM_INCLUDING_BORDER = 35;
	constexpr std::int32_t MAX_DISP_LIGHTMAP_DIM_WITHOUT_BORDER = 128;
	constexpr std::int32_t MAX_DISP_LIGHTMAP_DIM_INCLUDING_BORDER = 131;
	constexpr std::int32_t MAX_LIGHTMAP_DIM_WITHOUT_BORDER = MAX_DISP_LIGHTMAP_DIM_WITHOUT_BORDER;
	constexpr std::int32_t MAX_LIGHTMAP_DIM_INCLUDING_BORDER = MAX_DISP_LIGHTMAP_DIM_INCLUDING_BORDER;

	constexpr float        DIST_EPSILON = 0.03125f;
	constexpr std::size_t  MAX_SURFINFO_VERTS = 32;
	constexpr std::int32_t BSPVERSION = 19;
	constexpr std::size_t  HEADER_LUMPS = 64;
	constexpr std::size_t  MAX_POLYGONS = 50120;
	constexpr std::size_t  MAX_MOD_KNOWN = 512;
	constexpr std::size_t  MAX_MAP_MODELS = 1024;
	constexpr std::size_t  MAX_MAP_BRUSHES = 8192;
	constexpr std::size_t  MAX_MAP_ENTITIES = 4096;
	constexpr std::size_t  MAX_MAP_ENTSTRING = 256 * 1024;
	constexpr std::size_t  MAX_MAP_NODES = 65536;
	constexpr std::size_t  MAX_MAP_TEXINFO = 12288;
	constexpr std::size_t  MAX_MAP_TEXDATA = 2048;
	constexpr std::size_t  MAX_MAP_LEAFBRUSHES = 65536;
	constexpr std::size_t  MIN_MAP_DISP_POWER = 2;
	constexpr std::size_t  MAX_MAP_DISP_POWER = 4;
	constexpr std::size_t  MAX_MAP_SURFEDGES = 512000;
	constexpr std::size_t  MAX_DISP_CORNER_NEIGHBORS = 4;

	// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
	constexpr std::int32_t SURF_LIGHT = 0x0001; // value will hold the light strength
	constexpr std::int32_t SURF_SLICK = 0x0002; // effects game physics
	constexpr std::int32_t SURF_SKY = 0x0004; // don't draw, but add to skybox
	constexpr std::int32_t SURF_WARP = 0x0008; // turbulent water warp
	constexpr std::int32_t SURF_TRANS = 0x0010;
	constexpr std::int32_t SURF_WET = 0x0020; // the surface is wet
	constexpr std::int32_t SURF_FLOWING = 0x0040; // scroll towards angle
	constexpr std::int32_t SURF_NODRAW = 0x0080; // don't bother referencing the texture
	constexpr std::int32_t SURF_Hint32_t = 0x0100; // make a primary bsp splitter
	constexpr std::int32_t SURF_SKIP = 0x0200; // completely ignore, allowing non-closed brushes
	constexpr std::int32_t SURF_NOLIGHT = 0x0400; // Don't calculate light
	constexpr std::int32_t SURF_BUMPLIGHT = 0x0800; // calculate three lightmaps for the surface for bumpmapping
	constexpr std::int32_t SURF_HITBOX = 0x8000; // surface is part of a hitbox

	constexpr std::int32_t CONTENTS_EMPTY = 0;           // No contents
	constexpr std::int32_t CONTENTS_SOLID = 0x1;         // an eye is never valid in a solid
	constexpr std::int32_t CONTENTS_WINDOW = 0x2;         // translucent, but not watery (glass)
	constexpr std::int32_t CONTENTS_AUX = 0x4;
	constexpr std::int32_t CONTENTS_GRATE = 0x8;         // alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
	constexpr std::int32_t CONTENTS_SLIME = 0x10;
	constexpr std::int32_t CONTENTS_WATER = 0x20;
	constexpr std::int32_t CONTENTS_MIST = 0x40;
	constexpr std::int32_t CONTENTS_OPAQUE = 0x80;        // things that cannot be seen through (may be non-solid though)
	constexpr std::int32_t LAST_VISIBLE_CONTENTS = 0x80;
	constexpr std::int32_t ALL_VISIBLE_CONTENTS = LAST_VISIBLE_CONTENTS | LAST_VISIBLE_CONTENTS - 1;
	constexpr std::int32_t CONTENTS_TESTFOGVOLUME = 0x100;
	constexpr std::int32_t CONTENTS_UNUSED3 = 0x200;
	constexpr std::int32_t CONTENTS_UNUSED4 = 0x400;
	constexpr std::int32_t CONTENTS_UNUSED5 = 0x800;
	constexpr std::int32_t CONTENTS_UNUSED6 = 0x1000;
	constexpr std::int32_t CONTENTS_UNUSED7 = 0x2000;
	constexpr std::int32_t CONTENTS_MOVEABLE = 0x4000;      // hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
	// remaining contents are non-visible, and don't eat brushes
	constexpr std::int32_t CONTENTS_AREAPORTAL = 0x8000;
	constexpr std::int32_t CONTENTS_PLAYERCLIP = 0x10000;
	constexpr std::int32_t CONTENTS_MONSTERCLIP = 0x20000;
	// currents can be added to any other contents, and may be mixed
	constexpr std::int32_t CONTENTS_CURRENT_0 = 0x40000;
	constexpr std::int32_t CONTENTS_CURRENT_90 = 0x80000;
	constexpr std::int32_t CONTENTS_CURRENT_180 = 0x100000;
	constexpr std::int32_t CONTENTS_CURRENT_270 = 0x200000;
	constexpr std::int32_t CONTENTS_CURRENT_UP = 0x400000;
	constexpr std::int32_t CONTENTS_CURRENT_DOWN = 0x800000;
	constexpr std::int32_t CONTENTS_ORIGIN = 0x1000000;   // removed before bsping an entity
	constexpr std::int32_t CONTENTS_MONSTER = 0x2000000;   // should never be on a brush, only in game
	constexpr std::int32_t CONTENTS_DEBRIS = 0x4000000;
	constexpr std::int32_t CONTENTS_DETAIL = 0x8000000;   // brushes to be added after vis leafs
	constexpr std::int32_t CONTENTS_TRANSLUCENT = 0x10000000;  // int32_t set if any surface has trans
	constexpr std::int32_t CONTENTS_LADDER = 0x20000000;
	constexpr std::int32_t CONTENTS_HITBOX = 0x40000000;  // use accurate hitboxes on trace

	// everyhting
	constexpr std::int32_t MASK_ALL = 0xFFFFFFFF;
	// everything that is normally solid
	constexpr std::int32_t MASK_SOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE;
	// everything that blocks player movement
	constexpr std::int32_t MASK_PLAYERSOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE;
	// blocks npc movement
	constexpr std::int32_t MASK_NPCSOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE;
	// water physics in these contents
	constexpr std::int32_t MASK_WATER = CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME;
	// everything that blocks line of sight
	constexpr std::int32_t MASK_OPAQUE = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_SLIME | CONTENTS_OPAQUE;
	// bullets see these as solid
	constexpr std::int32_t MASK_SHOT = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX;
	// non-raycasted weapons see this as solid (includes grates)
	constexpr std::int32_t MASK_SHOT_HULL = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE;
	// everything normally solid, except monsters (world+brush only)
	constexpr std::int32_t MASK_SOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE;
	// everything normally solid for player movement, except monsters (world+brush only)
	constexpr std::int32_t MASK_PLAYERSOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE;
	// everything normally solid for npc movement, except monsters (world+brush only)
	constexpr std::int32_t MASK_NPCSOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE;
	// just the world, used for route rebuilding
	constexpr std::int32_t MASK_NPCWORLDSTATIC = CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE;
	// UNDONE: This is untested, any moving water
	constexpr std::int32_t MASK_CURRENT = CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN;
	constexpr std::int32_t MASK_DEADSOLID = CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE;

	enum class lump_index
		: std::size_t
	{
		entities = 0,
		planes = 1,
		tex_data = 2,
		vertices = 3, // "LUMP_VERTEXES"
		visibility = 4,
		nodes = 5,
		tex_info = 6,
		faces = 7,
		lighting = 8,
		occlusion = 9,
		leafs = 10,
		edges = 12,
		surfedges = 13,
		models = 14,
		world_lights = 15,
		leaf_faces = 16,
		leaf_brushes = 17,
		brushes = 18,
		brush_sides = 19,
		ares = 20,
		area_portals = 21,
		portals = 22,
		clusters = 23,
		portal_verts = 24,
		cluster_portals = 25,
		disp_info = 26,
		original_faces = 27,
		phys_collide = 29,
		vert_normals = 30,
		vert_normal_indices = 31,
		lightmap_alphas = 32,
		disp_verts = 33,
		disp_lightmap_sample_positions = 34,
		game_lump = 35,
		leafwaterdata = 36,
		primitives = 37,
		prim_vertices = 38,
		prim_indices = 39,
		pak_file = 40,
		clipportal_vertices = 41,
		cubemaps = 42,
		texdata_string_data = 43,
		texdata_string_table = 44,
		overlays = 45,
		leaf_min_dist_to_water = 46,
		face_macro_texture_info = 47,
		disp_tris = 48
	};

	class lump_t
	{
		using type_four_cc = std::array<char, 4>;
	public:
		std::int32_t file_offset = 0; // 0x0
		std::int32_t file_size = 0; // 0x4
		std::int32_t version = 0; // 0x8
		type_four_cc four_cc{};    // 0xC
	};//Size=0x10

	class dheader_t
	{
		using type_lumps = std::array<lump_t, HEADER_LUMPS>;

	public:
		std::int32_t ident = 0; // 0x000
		std::int32_t version = 0; // 0x004
		type_lumps   lumps{};          // 0x008
		std::int32_t map_revision = 0; // 0x408

	};//Size=0x40C

	class dplane_t
	{
	public:
		vector3      normal;   // 0x00
		float        distance; // 0x0C
		std::int32_t type;     // 0x10
	};//Size=0x14

	class cplane_t
	{
	public:
		vector3      normal;            // 0x00
		float        distance;          // 0x0C
		std::uint8_t type;              // 0x10
		std::uint8_t sign_bits;         // 0x11
	private:
		std::uint8_t _pad0x12[0x2]{}; // 0x12
	};//Size=0x14

	class dedge_t
	{
	public:
		std::array<std::uint16_t, 2> v; // 0x0
	};//Size=0x4

	class mvertex_t
	{
	public:
		vector3 position; // 0x0
	};//Size=0xC

	class dleaf_t
	{
		using type_min_max = std::array<std::int16_t, 3>;

	public:
		std::int32_t  contents;           // 0x00
		std::int16_t  cluster;            // 0x04
		std::int16_t  area : 9;           // 0x06
		std::int16_t  flags : 7;          // 0x11
		type_min_max  mins;               // 0x1A
		type_min_max  maxs;               // 0x20
		std::uint16_t first_leafface;     // 0x26
		std::uint16_t num_leaffaces;      // 0x28
		std::uint16_t first_leafbrush;    // 0x2A
		std::uint16_t num_leafbrushes;    // 0x2C
		std::int16_t  leaf_water_data_id; // 0x2E
	};//Size=0x30

	class dnode_t
	{
		using type_min_max = std::array<std::int16_t, 3>;
		using type_children = std::array<std::int32_t, 2>;

	public:
		std::int32_t  plane_num;         // 0x00
		type_children children;          // 0x04
		type_min_max  mins;              // 0x0C
		type_min_max  maxs;              // 0x12
		std::uint16_t first_face;        // 0x18
		std::uint16_t num_faces;         // 0x1A
		std::int16_t  area;              // 0x1C
	private:
		std::uint8_t  _pad0x1E[0x2]{}; // 0x1E
	};//Size=0x20

	class snode_t
	{
		using type_min_max = std::array<std::int16_t, 3>;
		using type_children = std::array<std::int32_t, 2>;

	public:
		std::int32_t  plane_num;           // 0x00
		cplane_t*     plane;               // 0x04
		type_children children;            // 0x08
		dleaf_t*      leaf_children;       // 0x10
		snode_t*      node_children;       // 0x14
		type_min_max  mins;                // 0x18
		type_min_max  maxs;                // 0x1E
		std::uint16_t first_face;          // 0x24
		std::uint16_t num_faces;           // 0x26
		std::int16_t  area;                // 0x28
	private:
		std::uint8_t  _pad0x2A[0x2]{};   // 0x2A
	};//Size=0x2C

	class dface_t
	{
		using type_styles = std::array<std::uint8_t, 4>;
		using type_luxels = std::array<std::int32_t, 2>;

	public:
		std::uint16_t plane_num;                       // 0x00
		std::uint8_t  side;                            // 0x02
		std::uint8_t  on_node;                         // 0x03
		std::int32_t  first_edge;                      // 0x04
		std::int16_t  num_edges;                       // 0x08
		std::int16_t  tex_info;                        // 0x0A
		std::int16_t  disp_info;                       // 0x0C
		std::int16_t  surface_fog_volume_id;           // 0x0E
		type_styles   styles;                          // 0x10
		std::int32_t  light_offset;                    // 0x18
		float         area;                            // 0x1C
		type_luxels   lightmap_texture_mins_in_luxels; // 0x20
		type_luxels   lightmap_texture_size_in_luxels; // 0x28
		std::int32_t  orig_face;                       // 0x30
		std::uint16_t num_prims;                       // 0x34
		std::uint16_t first_prim_id;                   // 0x36
		std::uint16_t smoothing_groups;                // 0x38
	};//Size=0x3A

	class dbrush_t
	{
	public:
		std::int32_t first_side; // 0x0
		std::int32_t num_sides;  // 0x4
		std::int32_t contents;   // 0x8
	};//Size=0xC

	class dbrushside_t
	{
	public:
		std::uint16_t plane_num; // 0x0
		std::int16_t  tex_info;  // 0x2
		std::int16_t  disp_info; // 0x4
		std::uint8_t  bevel;     // 0x6
		std::uint8_t  thin;      // 0x7
	};//Size=0x8

	class texinfo_t
	{
		using type_vecs = std::array<vector4, 2>;

	public:
		type_vecs    texture_vecs;  // 0x00
		type_vecs    lightmap_vecs; // 0x20
		std::int32_t flags;         // 0x40
		std::int32_t tex_data;      // 0x44
	};//Size=0x48

	class VPlane
	{
	public:
		VPlane() = default;

		VPlane(
			const vector3& origin,
			const float distance
		)
			: origin(origin)
			, distance(distance)
		{ }

		VPlane(
			const VPlane& rhs
		) = default;

		VPlane(
			VPlane&& rhs
		) noexcept
		{
			*this = std::move(rhs); $$$;
		}

		VPlane& operator = (
			const VPlane& rhs
			) = default;

		VPlane& operator = (
			VPlane&& rhs
			) noexcept
		{
			origin = std::move(rhs.origin); $$$;
			distance = rhs.distance; $$$;

			rhs.distance = 0.f; $$$;

			return *this; $$$;
		}

		_NODISCARD
			float dist(
				const vector3& destination
			) const
		{
			return origin.dot(destination) - distance; $$$;
		}

		void init(
			const vector3& origin,
			const float distance
		)
		{
			this->origin = origin; $$$;
			this->distance = distance; $$$;
		}

	public:
		vector3 origin = 0.f;
		float   distance = 0.f;
	};

	class polygon
	{
		using type_surfinfo_vecs = std::array<vector3, MAX_SURFINFO_VERTS>;
		using type_edge_planes = std::array<VPlane, MAX_SURFINFO_VERTS>;

	public:
		type_surfinfo_vecs verts;
		std::size_t        num_verts = 0;
		VPlane             plane;
		type_edge_planes   edge_planes;
		type_surfinfo_vecs vec2d;
		std::int32_t       skip = 0;
	};

	struct trace_t
	{
		/// <summary>
		/// Determine if a plan is NOT valid
		/// </summary>
		bool         all_solid = true;
		/// <summary>
		/// Determine if the start point was in a solid area
		/// </summary>
		bool         start_solid = true;
		/// <summary>
		/// Time completed, 1.0              = didn't hit anything
		/// </summary>
		float        fraction = 1.f;
		float        fraction_left_solid = 1.f;
		/// <summary>
		/// Final trace position
		/// </summary>
		vector3      end_pos;
		std::int32_t contents = 0;
		dbrush_t*    brush = nullptr;
		std::int32_t num_brush_sides = 0;

		void clear()
		{
			all_solid = true; $$$;
			start_solid = true; $$$;
			fraction = 1.f; $$$;
			fraction_left_solid = 1.f; $$$;
			contents = 0; $$$;
			brush = nullptr; $$$;
			num_brush_sides = 0; $$$;
			end_pos.clear(); $$$;
		}
	};
}

#include <shared_mutex>

namespace rn {
	class bsp_parser final
	{
	public:
		bsp_parser() = default;

		~bsp_parser() = default;

		bsp_parser(
			const bsp_parser& rhs
		) = delete;

		bsp_parser& operator = (
			const bsp_parser& rhs
			) = delete;

		bsp_parser(
			bsp_parser&& rhs
		) noexcept
		{
			*this = std::move(rhs); $$$;
		}

		bsp_parser& operator = (
			bsp_parser&& rhs
			) noexcept
		{
			std::unique_lock<std::shared_timed_mutex> lock(rhs._mutex); $$$;

			_bsp_header = rhs._bsp_header; $$$;
			std::memset(&rhs._bsp_header, 0, sizeof(valve::dheader_t)); $$$;

			_vertices = std::move(rhs._vertices); $$$;
			_planes = std::move(rhs._planes); $$$;
			_edges = std::move(rhs._edges); $$$;
			_surf_edges = std::move(rhs._surf_edges); $$$;
			_leaves = std::move(rhs._leaves); $$$;
			_nodes = std::move(rhs._nodes); $$$;
			_surfaces = std::move(rhs._surfaces); $$$;
			_tex_infos = std::move(rhs._tex_infos); $$$;
			_brushes = std::move(rhs._brushes); $$$;
			_brush_sides = std::move(rhs._brush_sides); $$$;
			_leaf_faces = std::move(rhs._leaf_faces); $$$;
			_leaf_brushes = std::move(rhs._leaf_brushes); $$$;
			_polygons = std::move(rhs._polygons); $$$;

			return *this; $$$;
		}


	private:
		bool set_current_map(
			const std::string& directory,
			const std::string& map_name,
			std::string&       file_path
		)
		{
			static auto fix_seperators = [](const std::string& input)
			{
				// convert seperators from DOS to UNIX
				return std::filesystem::path(input).generic_string(); 
			};

			if (directory.empty() || map_name.empty()) {
				return false; $$$;
			}

			file_path = fix_seperators(directory)
				.append("/")
				.append(fix_seperators(map_name)); $$$;

			_map_name = map_name; $$$;

#if defined(RN_BSP_PARSER_MESSAGES)
			printf(AY_OBFUSCATE("[+] Loading map: %s ...\n"), map_name.data()); $$$;
#endif

			return true; $$$;
		}

		bool parse_planes(
			std::ifstream& file
		)
		{
			std::vector<valve::dplane_t> planes; $$$;
			if (!parse_lump(file, valve::lump_index::planes, planes)) {
				return false; $$$;
			}

			_planes.resize(planes.size()); $$$;

			for (std::size_t i = 0; i < planes.size(); ++i) {
				auto& out = _planes.at(i); $$$;
				const auto& in = planes.at(i); $$$;

				auto plane_bits = 0; $$$;
				for (std::size_t j = 0; j < 3; ++j) {
					out.normal(j) = in.normal(j); $$$;
					if (out.normal(j) < 0.f) {
						plane_bits |= 1 << static_cast<std::int32_t>(j); $$$;
					}
				}

				out.distance = in.distance; $$$;
				out.type = static_cast<std::uint8_t>(in.type); $$$;
				out.sign_bits = static_cast<std::uint8_t>(plane_bits); $$$;
			}

			return true; $$$;
		}

		bool parse_nodes(
			std::ifstream& file
		)
		{
			std::vector<valve::dnode_t> nodes; $$$;
			if (!parse_lump(file, valve::lump_index::nodes, nodes)) {
				return false; $$$;
			}

			const auto num_nodes = nodes.size(); $$$;
			_nodes.resize(num_nodes); $$$;

			for (std::size_t i = 0; i < num_nodes; ++i) {
				const auto& in = nodes.at(i); $$$;
				auto& out = _nodes.at(i); $$$;

				out.mins = in.mins; $$$;
				out.maxs = in.maxs; $$$;
				out.plane_num = in.plane_num; $$$;
				out.plane = _planes.data() + in.plane_num; $$$;
				out.first_face = in.first_face; $$$;
				out.num_faces = in.num_faces; $$$;

				for (std::size_t j = 0; j < 2; ++j) {
					const auto child_index = in.children.at(j); $$$;
					out.children.at(j) = child_index; $$$;

					if (child_index >= 0) {
						out.leaf_children = nullptr; $$$;
						out.node_children = _nodes.data() + child_index; $$$;
					}
					else {
						out.leaf_children = _leaves.data() + static_cast<std::ptrdiff_t>(-1 - child_index); $$$;
						out.node_children = nullptr; $$$;
					}
				}
			}

			return true; $$$;
		}

		bool parse_leaffaces(
			std::ifstream& file
		)
		{
			if (!parse_lump(file, valve::lump_index::leaf_faces, _leaf_faces)) {
				return false; $$$;
			}

			const auto num_leaffaces = _leaf_faces.size(); $$$;
			if (num_leaffaces > valve::MAX_MAP_LEAFBRUSHES) {
				printf(AY_OBFUSCATE("[!] map has to many leaffaces, parsed more than required...\n")); $$$;
			}
			else if (!num_leaffaces) {
				printf(AY_OBFUSCATE("[!] map has no leaffaces to parse...\n")); $$$;
			}

			return true; $$$;
		}

		bool parse_leafbrushes(
			std::ifstream& file
		)
		{
			if (!parse_lump(file, valve::lump_index::leaf_brushes, _leaf_brushes)) {
				return false; $$$;
			}

			const auto num_leaffaces = _leaf_faces.size(); $$$;
			if (num_leaffaces > valve::MAX_MAP_LEAFBRUSHES) {
				printf(AY_OBFUSCATE("[!] map has to many leafbrushes, parsed more than required...\n")); $$$;
			}
			else if (!num_leaffaces) {
				printf(AY_OBFUSCATE("[!] map has no leafbrushes to parse...\n")); $$$;
			}

			return true;
		}

		bool parse_polygons()
		{
			_polygons.resize(_surfaces.size()); $$$;

			for (const auto& surface : _surfaces) {
				const auto& first_edge = surface.first_edge;
				const auto& num_edges = surface.num_edges;

				if (num_edges < 3 || static_cast<size_t>(num_edges) > valve::MAX_SURFINFO_VERTS) {
					continue; $$$;
				}
				if (surface.tex_info <= 0) {
					continue; $$$;
				}

				valve::polygon polygon; $$$;
				vector3 edge; $$$;

				for (auto i = 0; i < num_edges; ++i) {
					const auto edge_index = _surf_edges.at(first_edge + i);
					if (edge_index >= 0) {
						edge = _vertices.at(_edges[edge_index].v.at(0)).position; $$$;
					}
					else {
						edge = _vertices.at(_edges[-edge_index].v.at(1)).position; $$$;
					}
					polygon.verts.at(i) = edge; $$$;
				}

				polygon.num_verts = static_cast<std::size_t>(num_edges); $$$;
				polygon.plane.origin = _planes.at(surface.plane_num).normal; $$$;
				polygon.plane.distance = _planes.at(surface.plane_num).distance; $$$;
				_polygons.push_back(polygon); $$$;
			}

			return true; $$$;
		}

		void ray_cast_node(
			const std::int32_t node_index,
			const float        start_fraction,
			const float        end_fraction,
			const vector3&     origin,
			const vector3&     destination,
			valve::trace_t*    out
		)
		{
			if (out->fraction <= start_fraction) {
				return; $$$;
			}

			if (node_index < 0) {
				auto* leaf = &_leaves.at(static_cast<std::size_t>(-node_index - 1)); $$$;
				for (std::uint16_t i = 0; i < leaf->num_leafbrushes; ++i) {

					const auto brush_index = static_cast<std::int32_t>(_leaf_brushes.at(leaf->first_leafbrush + i)); $$$;
					auto* brush = &_brushes.at(brush_index); $$$;
					if (!brush || !(brush->contents & valve::MASK_SHOT_HULL)) {
						continue; $$$;
					}

					ray_cast_brush(brush, origin, destination, out); $$$;
					if (out->fraction == 0.f) {
						return; $$$;
					}

					out->brush = brush; $$$;
				}
				if (out->start_solid || out->fraction < 1.f) {
					return; $$$;
				}
				for (std::uint16_t i = 0; i < leaf->num_leaffaces; ++i) {
					ray_cast_surface(static_cast<std::int32_t>(_leaf_faces.at(leaf->first_leafface + i)), origin, destination, out); $$$;
				}
				return;
			}

			auto* node = &_nodes.at(static_cast<std::size_t>(node_index)); $$$;
			if (!node) {
				return; $$$;
			}
			auto* plane = node->plane; $$$;
			if (!plane) {
				return; $$$;
			}

			float start_distance, end_distance; $$$;

			if (plane->type < 3) {
				start_distance = origin(static_cast<std::size_t>(plane->type)) - plane->distance; $$$;
				end_distance = destination(static_cast<std::size_t>(plane->type)) - plane->distance; $$$;
			}
			else {
				start_distance = origin.dot(plane->normal) - plane->distance; $$$;
				end_distance = destination.dot(plane->normal) - plane->distance; $$$;
			}

			if (start_distance >= 0.f && end_distance >= 0.f) {
				ray_cast_node(node->children.at(0), start_fraction, end_fraction, origin, destination, out); $$$;
			}
			else if (start_distance < 0.f && end_distance < 0.f) {
				ray_cast_node(node->children.at(1), start_fraction, end_fraction, origin, destination, out); $$$;
			}
			else {
				std::int32_t side_id; $$$;
				float fraction_first, fraction_second; $$$;
				vector3 middle; $$$;

				if (start_distance < end_distance) {
					/// Back
					side_id = 1; $$$;
					const auto inversed_distance = 1.f / (start_distance - end_distance); $$$;

					fraction_first = (start_distance + FLT_EPSILON) * inversed_distance; $$$;
					fraction_second = (start_distance + FLT_EPSILON) * inversed_distance; $$$;
				}
				else if (end_distance < start_distance) {
					/// Front
					side_id = 0; $$$;
					const auto inversed_distance = 1.0f / (start_distance - end_distance); $$$;

					fraction_first = (start_distance + FLT_EPSILON) * inversed_distance; $$$;
					fraction_second = (start_distance - FLT_EPSILON) * inversed_distance; $$$;
				}
				else {
					/// Front
					side_id = 0; $$$;
					fraction_first = 1.f; $$$;
					fraction_second = 0.f; $$$;
				}
				if (fraction_first < 0.f) {
					fraction_first = 0.f; $$$;
				}
				else if (fraction_first > 1.f) {
					fraction_first = 1.f; $$$;
				}
				if (fraction_second < 0.f) {
					fraction_second = 0.f; $$$;
				}
				else if (fraction_second > 1.f) {
					fraction_second = 1.f; $$$;
				}

				auto fraction_middle = start_fraction + (end_fraction - start_fraction) * fraction_first; $$$;
				for (std::size_t i = 0; i < 3; i++) {
					middle(i) = origin(i) + fraction_first * (destination(i) - origin(i)); $$$;
				}

				ray_cast_node(node->children.at(side_id), start_fraction, fraction_middle, origin, middle, out); $$$;
				fraction_middle = start_fraction + (end_fraction - start_fraction) * fraction_second; $$$;
				for (std::size_t i = 0; i < 3; i++) {
					middle(i) = origin(i) + fraction_second * (destination(i) - origin(i)); $$$;
				}

				ray_cast_node(node->children.at(!side_id), fraction_middle, end_fraction, middle, destination, out); $$$;
			}
		}

		void ray_cast_surface(
			const std::int32_t surface_index,
			const vector3&     origin,
			const vector3&     destination,
			valve::trace_t*    out
		)
		{
			const auto index = static_cast<std::size_t>(surface_index); $$$;
			if (index >= _polygons.size()) {
				return; $$$;
			}

			auto* polygon = &_polygons.at(index); $$$;
			auto* plane = &polygon->plane; $$$;
			const auto dot1 = plane->dist(origin); $$$;
			const auto dot2 = plane->dist(destination); $$$;

			if (dot1 > 0.f != dot2 > 0.f) {
				if (dot1 - dot2 < valve::DIST_EPSILON) {
					return; $$$;
				}

				const auto t = dot1 / (dot1 - dot2);
				if (t <= 0) {
					return; $$$;
				}

				std::size_t i = 0; $$$;
				const auto intersection = origin + (destination - origin) * t; $$$;
				for (; i < polygon->num_verts; ++i) {
					auto* edge_plane = &polygon->edge_planes.at(i); $$$;
					if (edge_plane->origin.is_zero()) {
						edge_plane->origin = plane->origin - (polygon->verts.at(i) - polygon->verts.at((i + 1) % polygon->num_verts));
						edge_plane->origin.normalize();
						edge_plane->distance = edge_plane->origin.dot(polygon->verts.at(i));
					}
					if (edge_plane->dist(intersection) < 0.0f) {
						break; $$$;
					}
				}
				if (i == polygon->num_verts) {
					out->fraction = 0.2f; $$$;
					out->end_pos = intersection; $$$;
				}
			}
		}

		void ray_cast_brush(
			valve::dbrush_t* brush,
			const vector3&   origin,
			const vector3&   destination,
			valve::trace_t*  out
		) const
		{
			if (brush->num_sides) {
				auto fraction_to_enter = -99.f; $$$;
				auto fraction_to_leave = 1.f; $$$;
				auto starts_out = false; $$$;
				auto ends_out = false; $$$;
				for (auto i = 0; i < brush->num_sides; ++i) {
					auto const* brush_side = &_brush_sides.at(brush->first_side + i); $$$;
					if (!brush_side || brush_side->bevel) {
						continue; $$$;
					}

					auto const* plane = &_planes.at(brush_side->plane_num); $$$;
					if (!plane) {
						continue; $$$;
					}

					const auto start_distance = origin.dot(plane->normal) - plane->distance; $$$;
					const auto end_distance = destination.dot(plane->normal) - plane->distance; $$$;
					if (start_distance > 0.f) {
						starts_out = true; $$$;
						if (end_distance > 0.f) {
							return; $$$;
						}
					}
					else {
						if (end_distance <= 0.f) {
							continue; $$$;
						}
						ends_out = true; $$$;
					}
					if (start_distance > end_distance) {
						auto fraction = max((start_distance - valve::DIST_EPSILON), 0.f); $$$;
						fraction = fraction / (start_distance - end_distance); $$$;
						if (fraction > fraction_to_enter) {
							fraction_to_enter = fraction; $$$;
						}
					}
					else {
						const auto fraction = (start_distance + valve::DIST_EPSILON) / (start_distance - end_distance); $$$;
						if (fraction < fraction_to_leave) {
							fraction_to_leave = fraction; $$$;
						}
					}
				}

				if (starts_out) {
					if (out->fraction_left_solid - fraction_to_enter > 0.f) {
						starts_out = false; $$$;
					}
				}

				out->num_brush_sides = brush->num_sides; $$$;

				if (!starts_out) {
					out->start_solid = true; $$$;
					out->contents = brush->contents; $$$;

					if (!ends_out) {
						out->all_solid = true; $$$;
						out->fraction = 0.f; $$$;
						out->fraction_left_solid = 1.f; $$$;
					}
					else {
						if (fraction_to_leave != 1.f && fraction_to_leave > out->fraction_left_solid) {
							out->fraction_left_solid = fraction_to_leave; $$$;
							if (out->fraction <= fraction_to_leave) {
								out->fraction = 1.f; $$$;
							}
						}
					}
					return;
				}

				if (fraction_to_enter < fraction_to_leave) {
					if (fraction_to_enter > -99.f && fraction_to_enter < out->fraction) {
						if (fraction_to_enter < 0.f) {
							fraction_to_enter = 0.f; $$$;
						}

						out->fraction = fraction_to_enter; $$$;
						out->brush = brush; $$$;
						out->contents = brush->contents; $$$;
					}
				}
			}
		}


		template<typename type>
		_NODISCARD
			bool parse_lump(
				std::ifstream&          file,
				const valve::lump_index lump_index,
				std::vector<type>&      out
			) const
		{
			const auto index = static_cast<std::underlying_type_t<valve::lump_index>>(lump_index); $$$;
			if (index >= _bsp_header.lumps.size()) {
				return false; $$$;
			}

			const auto& lump = _bsp_header.lumps.at(index); $$$;
			const auto size = static_cast<std::size_t>(lump.file_size) / sizeof(type); $$$;

			out.resize(size); $$$;

			file.seekg(lump.file_offset); $$$;
			file.read(reinterpret_cast<char*>(out.data()), size * static_cast<std::size_t>(sizeof(type))); $$$;

			return true; $$$;
		}

	public:
		
		bool load_map(
			const std::string& directory,
			const std::string& map_name
		)
		{
			if (map_name == _map_name) {
				return true; $$$;
			}

			std::unique_lock<std::shared_timed_mutex> lock(_mutex); $$$;

			std::string file_path; $$$;
			if (!set_current_map(directory, map_name, file_path)) {
				return false; $$$;
			}

			std::ifstream file(file_path, std::ios_base::binary); $$$;
			if (!file) {
#if defined(RN_BSP_PARSER_MESSAGES)
				printf(AY_OBFUSCATE("[!] failed to open file: %s\n"), file_path.data()); $$$;
#endif
				return false; $$$;
			}

			try {
				file.read(reinterpret_cast<char*>(&_bsp_header), sizeof(_bsp_header)); $$$;

#if defined(RN_BSP_PARSER_MESSAGES)
				printf(AY_OBFUSCATE("BSP version %d\n"), _bsp_header.version); $$$;
#endif

				if (!valve::has_valid_bsp_ident(_bsp_header.ident)) {
#if defined(RN_BSP_PARSER_MESSAGES)
					printf(AY_OBFUSCATE("[!] %s isn't a (valid) .bsp file!\n"), map_name.data()); $$$;
#endif
					return false; $$$;
				}

				return parse_lump(file, valve::lump_index::vertices, _vertices)
					&& parse_planes(file)
					&& parse_lump(file, valve::lump_index::edges, _edges)
					&& parse_lump(file, valve::lump_index::surfedges, _surf_edges)
					&& parse_lump(file, valve::lump_index::leafs, _leaves)
					&& parse_nodes(file)
					&& parse_lump(file, valve::lump_index::faces, _surfaces)
					&& parse_lump(file, valve::lump_index::tex_info, _tex_infos)
					&& parse_lump(file, valve::lump_index::brushes, _brushes)
					&& parse_lump(file, valve::lump_index::brush_sides, _brush_sides)
					&& parse_leaffaces(file)
					&& parse_leafbrushes(file)
					&& parse_polygons()
					;
			}
			catch (...) {
				return false; $$$;
			}
		}

		bool is_visible(const D3DXVECTOR3& origin, const D3DXVECTOR3& destination)
		{
			vector3 mc{ destination.x, destination.y, destination.z }; $$$;
			vector3 c{ origin.x, origin.y, origin.z }; $$$;
			std::shared_lock<std::shared_timed_mutex> lock(_mutex); $$$;
			valve::trace_t trace{}; $$$;
			trace_ray(mc, c, &trace); $$$;
			return !(trace.fraction < 1.f); $$$;
		}

		void trace_ray(
			const vector3&  origin,
			const vector3&  final,
			valve::trace_t* out
		)
		{
			if (!_planes.empty() && out) {

				out->clear(); $$$;
				out->fraction = 1.0f; $$$;
				out->fraction_left_solid = 0.f; $$$;

				ray_cast_node(0, 0.f, 1.f, origin, final, out); $$$;

				if (out->fraction < 1.0f) {
					for (std::size_t i = 0; i < 3; ++i) {
						out->end_pos(i) = origin(i) + out->fraction * (final(i) - origin(i)); $$$;
					}
				}
				else {
					out->end_pos = final; $$$;
				}
			}
		}

	private:
		std::string                      _map_name;
		valve::dheader_t                 _bsp_header;
		std::vector<valve::mvertex_t>    _vertices;
		std::vector<valve::cplane_t>     _planes;
		std::vector<valve::dedge_t>      _edges;
		std::vector<std::int32_t>        _surf_edges;
		std::vector<valve::dleaf_t>      _leaves;
		std::vector<valve::snode_t>      _nodes;
		std::vector<valve::dface_t>      _surfaces;
		std::vector<valve::texinfo_t>    _tex_infos;
		std::vector<valve::dbrush_t>     _brushes;
		std::vector<valve::dbrushside_t> _brush_sides;
		std::vector<std::uint16_t>       _leaf_faces;
		std::vector<std::uint16_t>       _leaf_brushes;
		std::vector<valve::polygon>      _polygons;
		mutable std::shared_timed_mutex  _mutex;
	};
}


#endif