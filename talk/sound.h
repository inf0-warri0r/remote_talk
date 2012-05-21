
#include <alsa/asoundlib.h>

char *buf;
snd_pcm_uframes_t frames;
snd_pcm_t *capture_handle;

void set_hw(int max){
	int err;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_uframes_t f = max;
	unsigned int n = 44100;

	if ((err = snd_pcm_open (&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		perror("WTF! :");
		exit (1);
	}
		   
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		perror("WTF! :");
		exit (1);
	}
				 
	if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
		perror("WTF! :");
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		perror("WTF! :");
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		perror("WTF! :");
		exit (1);
	}
	if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &n, 0)) < 0) {
		perror("WTF! :");
		exit (1);
	}

	if ((err = snd_pcm_hw_params_set_period_size_near (capture_handle, hw_params, &f, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
			snd_strerror (err));
		exit (1);
	}
	if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
		perror("WTF! :");
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
		perror("WTF! :");
		exit (1);
	}
	snd_pcm_hw_params_free (hw_params);
}
void set_sw(int max){

	int err;
	snd_pcm_uframes_t f = max;
	snd_pcm_sw_params_t *sw_params;
	
	if((err = snd_pcm_sw_params_malloc(&sw_params)) < 0){
		perror("WTF! :");
		exit(1);
	}
	if((err = snd_pcm_sw_params_current(capture_handle, sw_params)) < 0){
		perror("WTF! :");
		exit(1);
	}
	if((err = snd_pcm_sw_params_set_start_threshold(capture_handle, sw_params, f)) < 0){
		perror("WTF! :");
		exit(1);
	}
	if((err = snd_pcm_sw_params_set_avail_min(capture_handle, sw_params, f)) < 0){
		perror("WTF! :");
		exit(1);
	}
	if((err = snd_pcm_sw_params(capture_handle, sw_params)) < 0){
		perror("WTF! :");
		exit(1);
	}
	snd_pcm_sw_params_free (sw_params);
}
void re_init(int max){
	int err;
	set_hw(max);
	set_sw(max);	

	if ((err = snd_pcm_prepare (capture_handle)) < 0) {
		perror("00ps! :");
		exit(1);
	}
}
void cap(int pid, int max){
	int err;
	while (1) {
		if ((err = snd_pcm_readi (capture_handle, buf, max)) != max) {
			perror("00ps! :");
			exit(1);
		}
		write(pid, buf, max*4);
	}
}
void cap_init(char *c)
{
	int max = 512;
	buf = malloc(4 * max);
	int sock = create_sock(c, 3999);
	if(sock  == 0) exit(0);
	re_init(max);
	int pfds[2];
	if(pipe(pfds) == -1){
		perror("WTF! pipe gone down MAN!!!");
		exit(1);
	}
	if(!fork()){
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		sendd(sock, 512, pfds[0]);	
	}else{
		cap(pfds[1], max);
	}
}



