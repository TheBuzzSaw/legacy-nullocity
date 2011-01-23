#ifndef THREAD_H
#define THREAD_H

#include <SDL.h>

namespace CGE
{
    class Thread
    {
        public:
            Thread();
            virtual ~Thread();

            void start(Uint32 inDelay = 0);
            void wait();
            void stopAndWait();

            inline void stop() { mStop = true; }
            inline bool isRunning() { return mRunning; }

            virtual void run() = 0;

        protected:
            inline bool stopRequested() { return mStop; }

        private:
            static int startThread(void* inData);

            volatile bool mRunning;
            volatile bool mStop;
            SDL_Thread* mThread;
    };
}

#endif
