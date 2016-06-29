#include <iostream>
#include<stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace std;

// Buffers to hold sound data.
ALuint Buffer;
ALuint Buffer2;
ALuint Buffer3;

// Sources are points of emitting sound.
ALuint Source;
ALuint Source2;
ALuint Source3;
/*
 * These are 3D cartesian vector coordinates. A structure or class would be
 * a more flexible of handling these, but for the sake of simplicity we will
 * just leave it as is.
 */

// Position of the source sound.
ALfloat SourcePos[] = { 1.0, 1.0, 1.0 };

// Velocity of the source sound.
ALfloat SourceVel[] = { 1.0, 0.0, 0.0 };

// Position of the Listener.
ALfloat ListenerPos[] = { 1.0, 1.0, 1.0 };

// Velocity of the Listener.
ALfloat ListenerVel[] = { 1.0, 1.0, 1.0 };

// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
// Also note that these should be units of '1'.
ALfloat ListenerOri[] = { 1.0, 1.0, 1.0,  1.0, 1.0, 1.0 };

/*
 * ALboolean LoadALData()
 *
 *         This function will load our sample data from the disk using the Alut
 *         utility and send the data into OpenAL as a buffer. A source is then
 *         also created to play that buffer.
 */
ALboolean LoadALData(char V[]="ghosteat.wav")
{
            // Variables to load into.

            ALenum format;
            ALsizei size=100;
            ALvoid* data;
            ALsizei freq=100;
            ALboolean loop=0;

            // Load wav data into a buffer.
            alGenBuffers(1, &Buffer);

            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

    // Load any of your favourite wav song here
            alutLoadWAVFile((ALbyte *)V, &format, &data, &size, &freq, &loop);
            alBufferData(Buffer, format, data, size, freq);
            alutUnloadWAV(format, data, size, freq);

            // Bind the buffer with the source.
            alGenSources(1, &Source);





            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

            alSourcei (Source, AL_BUFFER,   Buffer   );
            alSourcef (Source, AL_PITCH,    1.0      );
            alSourcef (Source, AL_GAIN,     1.0      );
            alSourcefv(Source, AL_POSITION, SourcePos);
            alSourcefv(Source, AL_VELOCITY, SourceVel);
            alSourcei (Source, AL_LOOPING,  loop     );



            //alSourcePlay(Source);

           // alutExit();
            // Do another error check and return.
            if(alGetError() == AL_NO_ERROR)
                        return AL_TRUE;

            return AL_TRUE;
}
ALboolean LoadALData2(char V[]="balleat.wav")
{
            // Variables to load into.

            ALenum format;
            ALsizei size=1;
            ALvoid* data;
            ALsizei freq=1;
            ALboolean loop=1;

            // Load wav data into a buffer.
            alGenBuffers(1, &Buffer2);

            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

    // Load any of your favourite wav song here
            alutLoadWAVFile((ALbyte *)V, &format, &data, &size, &freq, &loop);
            alBufferData(Buffer2, format, data, size, freq);
            alutUnloadWAV(format, data, size, freq);

            // Bind the buffer with the source.
            alGenSources(1, &Source2);





            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

            alSourcei (Source2, AL_BUFFER,   Buffer2   );
            alSourcef (Source2, AL_PITCH,    1.0      );
            alSourcef (Source2, AL_GAIN,     1.0      );
            alSourcefv(Source2, AL_POSITION, SourcePos);
            alSourcefv(Source2, AL_VELOCITY, SourceVel);
            alSourcei (Source2, AL_LOOPING,  loop     );



            //alSourcePlay(Source2);

           // alutExit();
            // Do another error check and return.
            if(alGetError() == AL_NO_ERROR)
                        return AL_TRUE;

            return AL_TRUE;
}



ALboolean LoadALData3(char V[]="fruiteat.wav")
{
            // Variables to load into.

            ALenum format;
            ALsizei size=1;
            ALvoid* data;
            ALsizei freq=1;
            ALboolean loop=1;

            // Load wav data into a buffer.
            alGenBuffers(1, &Buffer3);

            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

    // Load any of your favourite wav song here
            alutLoadWAVFile((ALbyte *)V, &format, &data, &size, &freq, &loop);
            alBufferData(Buffer3, format, data, size, freq);
            alutUnloadWAV(format, data, size, freq);

            // Bind the buffer with the source.
            alGenSources(1, &Source3);





            if(alGetError() != AL_NO_ERROR)
                        return AL_FALSE;

            alSourcei (Source3, AL_BUFFER,   Buffer3   );
            alSourcef (Source3, AL_PITCH,    1.0      );
            alSourcef (Source3, AL_GAIN,     1.0      );
            alSourcefv(Source3, AL_POSITION, SourcePos);
            alSourcefv(Source3, AL_VELOCITY, SourceVel);
            alSourcei (Source3, AL_LOOPING,  loop     );



            //alSourcePlay(Source2);

           // alutExit();
            // Do another error check and return.
            if(alGetError() == AL_NO_ERROR)
                        return AL_TRUE;

            return AL_TRUE;
}




















/*
 * void SetListenerValues()
 *
 *         We already defined certain values for the Listener, but we need
 *         to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues()
{
            alListenerfv(AL_POSITION,    ListenerPos);
            alListenerfv(AL_VELOCITY,    ListenerVel);
            alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
 * void KillALData()
 *
 *         We have allocated memory for our buffers and sources which needs
 *         to be returned to the system. This function frees that memory.
 */
void KillALData()
{
            alDeleteBuffers(1, &Buffer);
            alDeleteSources(1, &Source);
            alutExit();
}

/*int main(int argc, char *argv[])
{
            cout << "Play OpenAL waveform audio file" << endl;
            cout << "Type a character controls:" << endl;
            cout << "p) To Play" << endl;
            cout << "s) To Stop playing" << endl;
            cout << "h) To Hold / Pause playing" << endl;
            cout << "q) To Quit playing" << endl << endl;

            // Initialize OpenAL and clear the error bit.
            alutInit(NULL, 0);
            alGetError();

            // Load the wav data.
            if(LoadALData() == AL_FALSE) //method 1: LoadALData()
            {
                cout<<"Error loading data.";
                        return 0;
            }

            SetListenerValues(); //method 2: void SetListenerValues()

            // Setup an exit procedure.
            //atexit(KillALData); //method 3:
             //KillALData();

            // Loop.
            char c = ' ';
            cin>>c;
            while(c != 'q')
            {

                        switch(c)
                        {
                                    // Pressing 'p' will begin playing the sample.
                                    case 'p': alSourcePlay(Source); break;

                                    // Pressing 's' will stop the sample from playing.
                                    case 's': alSourceStop(Source); break;

                                    // Pressing 'h' will pause the sample.
                                    case 'h': alSourcePause(Source); break;
                        };
                        cin>>c;
            }
            return 0;
}*/
