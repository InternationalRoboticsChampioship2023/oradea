import cv2

# Function to capture video from multiple cameras
def capture_from_cameras(cameras, window_name='Combined Feed'):
    cap_list = [cv2.VideoCapture(cam) for cam in cameras]

    while True:
        frames = [cap.read()[1] for cap in cap_list]

        # Check if frames are available
        if all(frame is not None for frame in frames):
            # Arrange frames in a 2x2 grid
            top_row = cv2.hconcat([frames[0], frames[1]])
            bottom_row = cv2.hconcat([frames[2], frames[3]])
            combined_feed = cv2.vconcat([top_row, bottom_row])

            # Display the combined feed
            cv2.imshow(window_name, combined_feed)

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the video capture objects
    for cap in cap_list:
        cap.release()

    # Close all OpenCV windows
    cv2.destroyAllWindows()

# Specify the camera indices (0, 1, 2, 3, etc.)
camera_indices = [0, 1, 2, 3]

# Run the function with the specified camera indices
capture_from_cameras(camera_indices)
