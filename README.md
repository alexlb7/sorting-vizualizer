How to run:
  - Install python
  - Run these commands:
      - python3 -m venv .venv
      - source .venv/bin/activate
      - cd api
      - pip install -r requirements.txt
      - python3 manage.py runserver
  - Access the website at http://127.0.0.1:8000/

How it works:

Unlike the majority of sorting visualization mine was built in Django therefore i needed a particular backend-frontend interface to the visualization work. 
I used Event Source on the template to capture any generator sent by the view so i can display all changes of the array in real time.
The algorithms were written in cpp, that was the original idea so that's why i used a backend in spite of the default javascript algorithms to make visualizers.
Then i used the cpython interface to communicate export the algos and did a callback inside them everytime the array changes, and the interface receive the callback to push the array in to a queue.
The view creates the interface queue and when there is an new array in it do a yield to the frontend through the StreamingHttpsResponse.
