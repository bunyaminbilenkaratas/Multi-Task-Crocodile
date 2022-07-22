class Task{
		private:
			static int task_id;
			String task_name;
			int task_created_timer;
			static int number_of_running_tasks;
			static unsigned long min_interval;
			int task_interval;
			int now_timer_read;
			int previous_timer_read;
			
			unsigned long timer(){
				return millis(); // Use millis function for arduino. For other microprocessors use the function written for them.
			}
			
			void TestAndSet_Min_Interval(int interval){
				if (interval<1){
					Serial.println(" !!! Fatal error interval value cannot be less than 1 .");
					exit(1);
				}
				
				if (min_interval>interval)
				min_interval=interval;
				
				task_interval=interval;
			}
		
		public:
			Task(){
				task_id=++task_id;
        		String task_id_str = String(task_id);
				task_name="unnamed_task"+task_id_str;
				TestAndSet_Min_Interval(1000);
				task_created_timer=timer();
				number_of_running_tasks++;
			}
			
			Task(String task_name){
				task_id=++task_id;
				this->task_name=task_name;
				task_interval=1000;
				task_created_timer=timer();
				number_of_running_tasks++;
			}
			
			Task(String task_name, int task_interval){
				task_id=++task_id;
				this->task_name=task_name;
				this->task_interval=task_interval;
				task_created_timer=timer();
				number_of_running_tasks++;
			}
			
			~Task(){
				number_of_running_tasks--;
				
			}
			
			void Task_start(void (*content)()){
				int control_start_time=timer();
				now_timer_read=timer();
				if(now_timer_read-previous_timer_read>task_interval){
					previous_timer_read=now_timer_read;
					(*content)();
				}
				int control_stop_time=timer();
				if (control_start_time-control_stop_time>10000){
					Serial.println("ATTENTION !!! task duration took too long, this may destabilize other tasks.");
				}
				
			}
			
			int getTask_id(){
				return task_id;
			}
			 
			String getTask_name(){
				return task_name;
			}
			 
			void ChangeTask_name(String task_name){
			 	this->task_name=task_name;
			}
			
			void ChangeTask_interval(int task_interval){
				this->task_interval=task_interval;
			}
			 
			void Task_terminate(){
			 	delete this;
			}
		 };
