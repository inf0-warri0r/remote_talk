/*
*Author :Tharindra Galahena
*Project:walkie-talkie application for linux
*Date   :28/04/2012
*/

#include <stdio.h>
#include <alsa/asoundlib.h>
#include "listener.h"

char *buf;
snd_pcm_t *playback_handle;
snd_pcm_hw_params_t *hw_params;

void set_sw(int max){

	snd_pcm_uframes_t f = max;
	snd_pcm_sw_params_t *sw_params;

	snd_pcm_sw_params_malloc(&sw_params);
	snd_pcm_sw_params_current(playback_handle, sw_params);

	snd_pcm_sw_params_set_start_threshold(playback_handle, sw_params, f);

	snd_pcm_uframes_t bo = 0;

	snd_pcm_sw_params_get_boundary(sw_params, &bo);
	
	snd_pcm_sw_params_set_stop_threshold(playback_handle, sw_params, bo);
	snd_pcm_sw_params_set_silence_threshold(playback_handle, sw_params, 0);
	snd_pcm_sw_params_set_silence_size(playback_handle, sw_params, bo);
	snd_pcm_sw_params_set_avail_min(playback_handle, sw_params, f);

	snd_pcm_sw_params(playback_handle, sw_params);

	snd_pcm_sw_params_free (sw_params);
}
void set_hw(int max){
	int err;
	
	if ((err = snd_pcm_open (&playback_handle, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
			perror("WTF! :");
			exit (1);
		}
		   
		if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
			perror("WTF! :");
			exit (1);
		}
				 
		if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0) {
			perror("WTF! :");
			exit (1);
		}
	
		if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
			perror("WTF! :");
			exit (1);
		}
	
		if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
			perror("WTF! :");
			exit (1);
		}
		
		unsigned int n =  44100;
		if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &n, 0)) < 0) 		{
			perror("WTF! :");
			exit (1);
		}
		snd_pcm_uframes_t b = 1024;
		snd_pcm_uframes_t f = max;
		if ((err = snd_pcm_hw_params_set_buffer_size_near (playback_handle, hw_params, &b)) < 0) {
			perror("WTF! :");
			exit (1);
		}

		if ((err = snd_pcm_hw_params_set_period_size_near (playback_handle, hw_params, &f, NULL)) < 0) {
			perror("WTF! :");
			exit (1);
		}
		
		if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, 2)) < 0) {
			perror("WTF! :");
			exit (1);
		}
	
		if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0) {
			perror("WTF! :");
			exit (1);
		}
		snd_pcm_hw_params_free (hw_params);
}	
void p_init(int max){
	int err;
	set_hw(max);
	set_sw(max);
	if ((err = snd_pcm_prepare (playback_handle)) < 0) {
		perror("00ps! :");
		exit(1);
	}
	snd_pcm_writei (playback_handle, buf, max);
	snd_pcm_start(playback_handle);
		
}
void play(int pid, int max){
	int err;
	p_init(max);
	while (1) {
		read(pid, buf, max*4);
		if ((err = snd_pcm_writei (playback_handle, buf, max)) < 0) {
			snd_pcm_prepare (playback_handle);
		}
	}
	snd_pcm_drain (playback_handle);
	snd_pcm_close (playback_handle);
}

void rec(int sock, int pid, int max){
	int cc;
	while(1){
		if((cc = recive(sock, buf, max)) == -1){
			perror("00ps! :");
			exit(1);		
		}
		write(pid, buf, max*4);	
	}
}
void so_init()
{
	int max = 512;
	int sock = connect_sock();
	int pfds[2];
	if(pipe(pfds) == -1){
		perror("WTF! pipe gone down MAN!!!");
		exit(1);
	}

	buf = malloc(4 * max);

	if(!fork()){
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		rec(sock, pfds[1], max);	
	}else{
		system("sleep 1");
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		play(pfds[0], max);
	}
}
