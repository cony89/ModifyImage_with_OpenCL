/* Created by Alessandro Bigiotti */

#define MAX_SOURCE_SIZE (0x100000)

int InitializeOpenCL() {
 
  printf("Initialize Device...\n");

  strcat(strcpy(path_to_kernel, currentDirectory), "/filter_kernel.cl");

  // Select NVIDIA PLATFORM
  err = clGetPlatformIDs(10, Platform_id, &Num_Platform);
  if (err != CL_SUCCESS){
    printf("Errore, Impossibile ottenere una Piattaforma!\n");
    return EXIT_FAILURE;
  }

  // Select the NVIDIA Device for NVIDIA (Platform_id[1]) 
  err = clGetDeviceIDs(Platform_id[1], CL_DEVICE_TYPE_GPU, 10, Devices_id, &Num_Device);
  if (err != CL_SUCCESS){
    printf("Errore, Impossibile ottenere un Device!\n");
    return EXIT_FAILURE;
  }

  // Create a Context to Use the device
  context = clCreateContext(0, 1, Devices_id, NULL, NULL, &err);
  if (!context)
  {
    printf("Errore, Impossibile creare un contesto!\n");
    return EXIT_FAILURE;
  }

  // Create a Commands queue to run the kernel
  commands = clCreateCommandQueue(context, Devices_id[0], 0, &err);
  if (!commands)
  {
    printf("Errore, Impossibile creare coda di comando!\n");
    return EXIT_FAILURE;
  }

  // Load the .cl file
  fp = fopen(path_to_kernel, "r");
  if (!fp) {
	printf("Impossibile aprire il file kernel \n");
	return EXIT_FAILURE;
  }
  // Copy the .cl code into source_str
  source_str = (char *)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);

  // Create the Program with source "source_str"
  program = clCreateProgramWithSource(context, 1, (const char **)& source_str, (const size_t *)&source_size, &err);
  if (!program)
  {
	printf("Errore, Impossibile creare il programma!\n");
	scanf("%d", e);
	return EXIT_FAILURE;
  }

  // Compile the .cl code
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS)	{
	size_t len;
	char buffer[2048];
	printf("Errore, Impossibile creare l'eseguibile!\n");
	// Show some information about the building of the program
	clGetProgramBuildInfo(program, Devices_id[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
	printf("%s\n", buffer);
	scanf("%d",e);
	exit(1);
  }

}
