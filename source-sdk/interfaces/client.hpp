#pragma once

class IClient {
public:
	VF( GetAllClasses, ClientClass*, 8 );
};


class CClientState {
	class c_clock_drift_mgr {
	public:
		float clock_offsets[ 17 ];
		std::uint32_t current_clock_offset;
		std::uint32_t server_tick;
		std::uint32_t client_tick;
	};

	public:
		void request_full_update( ) {
			delta_tick = -1;
		}

		char pad1[ 156 ];
		NetChannel* net_channel;
		std::uint32_t challenge_nr;
		char pad2[ 100 ];
		std::uint32_t signon_state;
		char pad3[ 8 ];
		float next_cmd_time;
		std::uint32_t server_count;
		std::uint32_t current_sequence;
		char pad4[ 8 ];
		c_clock_drift_mgr clock_drift_mgr;
		std::uint32_t delta_tick;
		bool paused;
		char pad5[ 3 ];
		std::uint32_t view_entity;
		std::uint32_t player_slot;
		char level_name[ 260 ];
		char level_name_short[ 80 ];
		char group_name[ 80 ];
		char pad6[ 92 ];
		std::uint32_t max_clients;
		char pad7[ 18820 ];
		float last_server_tick_time;
		bool insimulation;
		char pad8[ 3 ];
		unsigned int oldtickcount;
		float tick_remainder;
		float frame_time;
		std::uint32_t last_outgoing_command;
		std::uint32_t choked_commands;
		std::uint32_t last_command_ack;
		std::uint32_t command_ack;
		std::uint32_t sound_sequence;
		char pad9[ 80 ];
		Vec3D viewangles;
};